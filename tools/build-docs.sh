#!/usr/bin/env bash

set -euo pipefail

usage() {
    echo "Usage: $0 [--tag vMAJOR.MINOR.PATCH] [--refresh-api] [--no-local-copy] [--output-dir PATH]"
    echo
    echo "Installs missing documentation tools, generates all PDG documentation,"
    echo "and creates a versioned documentation archive."
    echo
    echo "Doxygen always regenerates C++ HTML, JavaScript HTML, and JavaScript man pages."
    echo "--refresh-api also refreshes JavaScript API declarations using the built pdg executable."
    echo "Generated pages also replace docs/cxx/html, docs/javascript/html, docs/javascript/man, and docs/typescript/html."
    echo "--no-local-copy keeps the generated pages only in the artifact site."
    echo "Artifacts default to artifacts/docs/; Doxygen logs are in its work/ directory."
}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PDG_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RELEASE_TAG=""
REFRESH_API=0
UPDATE_LOCAL_DOCS=1
OUTPUT_DIR="$PDG_ROOT/artifacts/docs"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --tag)
            RELEASE_TAG="${2:?--tag requires a value}"
            shift 2
            ;;
        --refresh-api)
            REFRESH_API=1
            shift
            ;;
        --no-local-copy)
            UPDATE_LOCAL_DOCS=0
            shift
            ;;
        --output-dir)
            OUTPUT_DIR="${2:?--output-dir requires a value}"
            shift 2
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

install_doc_tools() {
    if command -v doxygen >/dev/null 2>&1 && command -v dot >/dev/null 2>&1; then
        return
    fi

    case "$(uname -s)" in
        Darwin)
            if ! command -v brew >/dev/null 2>&1; then
                echo "Homebrew is required to install Doxygen and Graphviz on macOS." >&2
                exit 1
            fi
            brew install doxygen graphviz
            ;;
        Linux)
            if ! command -v apt-get >/dev/null 2>&1; then
                echo "apt-get is required to install Doxygen and Graphviz on Linux." >&2
                exit 1
            fi
            local apt_command=(apt-get)
            if [[ "$(id -u)" -ne 0 ]]; then
                if ! command -v sudo >/dev/null 2>&1; then
                    echo "sudo is required to install Doxygen and Graphviz." >&2
                    exit 1
                fi
                apt_command=(sudo apt-get)
            fi
            "${apt_command[@]}" update
            "${apt_command[@]}" install -y doxygen graphviz
            ;;
        *)
            echo "Automatic documentation-tool installation is supported on macOS and apt-based Linux." >&2
            exit 1
            ;;
    esac

    command -v doxygen >/dev/null 2>&1 || { echo "Doxygen installation failed." >&2; exit 1; }
    command -v dot >/dev/null 2>&1 || { echo "Graphviz installation failed." >&2; exit 1; }
}

if [[ -n "$RELEASE_TAG" ]]; then
    cmake -DPDG_SOURCE_DIR="$PDG_ROOT" -DRELEASE_TAG="$RELEASE_TAG" \
        -P "$PDG_ROOT/cmake/ValidateReleaseVersion.cmake"
fi

install_doc_tools
echo "Using Doxygen $(doxygen --version)."

if [[ $REFRESH_API -eq 1 ]]; then
    if [[ ! -x "$PDG_ROOT/pdg" ]]; then
        echo "A built pdg executable is required by --refresh-api. Run make pdg first." >&2
        exit 1
    fi
    echo "Refreshing JavaScript API declarations from the built pdg executable..."
    "$PDG_ROOT/tools/make-idl-javascript.sh"
else
    echo "Using JavaScript API declarations in docs/javascript/pdg-js.h."
    echo "To refresh those declarations from a built pdg executable, use --refresh-api."
fi

PDG_VERSION="$(tr -d '[:space:]' < "$PDG_ROOT/VERSION")"
DOC_BASENAME="pdg-docs-v${PDG_VERSION}"
SITE_DIR="$OUTPUT_DIR/site/$DOC_BASENAME"
ASSET_PATH="$OUTPUT_DIR/$DOC_BASENAME.zip"
WORK_DIR="$OUTPUT_DIR/work"

cmake -E remove_directory "$SITE_DIR"
cmake -E remove_directory "$WORK_DIR"
cmake -E make_directory "$SITE_DIR/cxx" "$SITE_DIR/javascript" "$SITE_DIR/third-party" "$WORK_DIR"

run_doxygen() {
    local source_dir="$1"
    local config_file="$2"
    local destination="$3"
    local log_file="$4"
    local description="$5"
    local generated_config="$WORK_DIR/$(basename "$log_file" .log).Doxyfile"
    local execution_log="$WORK_DIR/$(basename "$log_file" -warnings.log)-doxygen.log"

    cp "$source_dir/$config_file" "$generated_config"
    {
        echo "OUTPUT_DIRECTORY = $destination"
        echo "PROJECT_NUMBER = v$PDG_VERSION"
        echo "WARN_LOGFILE = $log_file"
        echo "HAVE_DOT = YES"
        echo "DOT_PATH = $(dirname "$(command -v dot)")"
        if [[ "$source_dir" == "$PDG_ROOT/docs/cxx" ]]; then
            echo "IMAGE_PATH = $PDG_ROOT/docs"
        fi
    } >> "$generated_config"
    echo "Regenerating $description with Doxygen ($config_file)..."
    echo "  Output: $destination"
    echo "  Progress log: $execution_log"
    echo "  Warnings: $log_file"
    local attempt
    for attempt in 1 2 3; do
        if (cd "$source_dir" && doxygen "$generated_config" > "$execution_log" 2>&1); then
            echo "Generated $description."
            return
        fi
        if [[ $attempt -lt 3 ]]; then
            echo "Doxygen failed for $source_dir (attempt $attempt of 3); retrying." >&2
        fi
    done

    echo "Doxygen failed three times for $source_dir. Last output:" >&2
    tail -n 100 "$execution_log" >&2
    return 1
}

if ! command -v node >/dev/null 2>&1 || ! command -v npm >/dev/null 2>&1; then
    echo "Node.js and npm are required for the TypeScript reference." >&2
    exit 1
fi
npm ci --prefix "$PDG_ROOT/tools/typescript" --ignore-scripts --no-audit --no-fund
if [[ $REFRESH_API -eq 1 ]]; then
    node "$PDG_ROOT/tools/typescript/generate.js"
fi
node "$PDG_ROOT/tools/typescript/build-docs.js" "$SITE_DIR/typescript/html"

run_doxygen "$PDG_ROOT/docs/cxx" Doxyfile "$SITE_DIR/cxx" "$WORK_DIR/cxx-warnings.log" "C++ HTML"
run_doxygen "$PDG_ROOT/docs/javascript" Doxyfile "$SITE_DIR/javascript" "$WORK_DIR/javascript-warnings.log" "JavaScript HTML"
run_doxygen "$PDG_ROOT/docs/javascript" Doxyfile-man "$SITE_DIR/javascript" "$WORK_DIR/man-warnings.log" "JavaScript manual pages"

{
    echo '<!doctype html><html lang="en"><head><meta charset="utf-8">'
    echo '<meta name="viewport" content="width=device-width, initial-scale=1">'
    echo '<title>PDG JavaScript manual pages</title></head><body>'
    echo '<h1>PDG JavaScript manual pages</h1><ul>'
    while IFS= read -r man_page; do
        man_name="$(basename "$man_page")"
        man_href="${man_page#"$SITE_DIR/javascript/man/"}"
        printf '<li><a href="%s">%s</a></li>\n' "$man_href" "$man_name"
    done < <(find "$SITE_DIR/javascript/man" -type f ! -name index.html | sort)
    echo '</ul></body></html>'
} > "$SITE_DIR/javascript/man/index.html"

cmake -E copy_directory "$PDG_ROOT/docs/chipmunk" "$SITE_DIR/third-party/chipmunk"
cmake -E copy_directory "$PDG_ROOT/docs/libjpeg-turbo" "$SITE_DIR/third-party/libjpeg-turbo"
cmake -E copy "$PDG_ROOT/LICENSE" "$SITE_DIR/LICENSE"
cmake -E copy "$PDG_ROOT/README.md" "$SITE_DIR/README.md"
cmake -E copy "$PDG_ROOT/VERSION" "$SITE_DIR/VERSION"

cat > "$SITE_DIR/index.html" <<EOF
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>PDG v${PDG_VERSION} Documentation</title>
  <style>
    body { font: 18px/1.5 system-ui, sans-serif; margin: 4rem auto; max-width: 48rem; padding: 0 1.5rem; color: #20242a; }
    h1 { line-height: 1.15; }
    li { margin: .65rem 0; }
    a { color: #1769aa; }
  </style>
</head>
<body>
  <h1>Pixel Dust Game Engine v${PDG_VERSION}</h1>
  <p>API documentation and bundled third-party references.</p>
  <ul>
    <li><a href="cxx/html/index.html">C++ API</a></li>
    <li><a href="javascript/html/index.html">JavaScript API</a></li>
    <li><a href="typescript/html/index.html">TypeScript API and MVC</a></li>
    <li><a href="javascript/man/">JavaScript manual pages</a></li>
    <li><a href="third-party/chipmunk/API-Reference/index.html">Chipmunk reference</a></li>
    <li><a href="third-party/libjpeg-turbo/">libjpeg-turbo reference</a></li>
  </ul>
</body>
</html>
EOF

for required_file in \
    "$SITE_DIR/index.html" \
    "$SITE_DIR/cxx/html/index.html" \
    "$SITE_DIR/javascript/html/index.html" \
    "$SITE_DIR/javascript/man/index.html" \
    "$SITE_DIR/typescript/html/index.html"; do
    if [[ ! -f "$required_file" ]]; then
        echo "Documentation output is missing: $required_file" >&2
        exit 1
    fi
done

if ! find "$SITE_DIR/javascript/man" -type f -print -quit | grep -q .; then
    echo "JavaScript manual pages were not generated." >&2
    exit 1
fi

if [[ $UPDATE_LOCAL_DOCS -eq 1 ]]; then
    echo "Refreshing the generated documentation under docs/..."
    # Replace each generated tree so removed API pages cannot survive a rebuild.
    for generated_tree in cxx/html javascript/html javascript/man typescript/html; do
        cmake -E remove_directory "$PDG_ROOT/docs/$generated_tree"
        cmake -E copy_directory "$SITE_DIR/$generated_tree" "$PDG_ROOT/docs/$generated_tree"
    done
    echo "Local C++ API: $PDG_ROOT/docs/cxx/html/index.html"
    echo "Local JavaScript API: $PDG_ROOT/docs/javascript/html/index.html"
fi

echo "Packaging regenerated documentation: $ASSET_PATH"
cmake -E make_directory "$OUTPUT_DIR"
cmake -E rm -f "$ASSET_PATH" "$ASSET_PATH.sha256"
(
    cd "$OUTPUT_DIR/site"
    cmake -E tar cf "$ASSET_PATH" --format=zip -- "$DOC_BASENAME"
)

if command -v shasum >/dev/null 2>&1; then
    (cd "$OUTPUT_DIR" && shasum -a 256 "$(basename "$ASSET_PATH")" > "$(basename "$ASSET_PATH").sha256")
else
    (cd "$OUTPUT_DIR" && sha256sum "$(basename "$ASSET_PATH")" > "$(basename "$ASSET_PATH").sha256")
fi

warning_count="$(find "$WORK_DIR" -name '*-warnings.log' -type f -exec cat {} + | wc -l | tr -d '[:space:]')"
echo "Generated documentation with $warning_count Doxygen warning(s)."
echo "Site: $SITE_DIR/index.html"
echo "Doxygen logs: $WORK_DIR"
echo "Created $ASSET_PATH"
echo "Created $ASSET_PATH.sha256"
