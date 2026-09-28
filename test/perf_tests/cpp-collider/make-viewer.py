#!/usr/bin/env python3
"""Record native benchmark trajectories and package a standalone HTML player."""
import argparse
import base64
import gzip
import json
from pathlib import Path
import subprocess
import re
import tempfile


def main():
    source = Path(__file__).resolve().parent
    root = source.parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary', type=Path, default=root/'build/darwin/arm64/pdg/src/pdg-collider-perf')
    parser.add_argument('--output', type=Path, default=root/'artifacts/collider-viewer/index.html')
    parser.add_argument('--from-viewer', type=Path, help='Reuse a saved viewer without running the benchmark')
    parser.add_argument('--compact', action='store_true', help='Embed losslessly compressed recordings for distribution')
    parser.add_argument('--owner', choices=['both', 'sprite', 'part'], default='both')
    parser.add_argument('--bodies', type=int, default=2000)
    parser.add_argument('--steps', type=int, default=2000)
    parser.add_argument('--no-sleep', action='store_true', help='Omit the optional sleeping-enabled recordings')
    args = parser.parse_args()
    if args.bodies < 2 or args.steps < 1:
        parser.error('--bodies must be at least 2 and --steps must be positive')
    if args.from_viewer:
        saved = args.from_viewer.read_text()
        match = re.search(r'<script\b[^>]*\bid="recordings"[^>]*>(.*?)</script>', saved, re.S)
        if not match:
            parser.error('Saved viewer has no embedded recordings')
        payload = match.group(1)
        if 'data-encoding="gzip-base64"' in match.group(0).split('>', 1)[0]:
            payload = gzip.decompress(base64.b64decode(payload, validate=True)).decode('utf-8')
        data = json.loads(payload)
        if data.get('version') != 1:
            parser.error('Unsupported recording format version')
        recordings = data['recordings']
    else:
        binary = args.binary.resolve()
        if not binary.is_file():
            parser.error(f'Build pdg-collider-perf first; executable not found: {binary}')
        recordings = []
        with tempfile.TemporaryDirectory(prefix='pdg-collider-viewer-') as temp:
            for owner in (['sprite', 'part'] if args.owner == 'both' else [args.owner]):
                for scenario, sleep in ([('approach', False), ('contacts', False), ('quality', False)] + ([] if args.no_sleep else [('quality', True)])):
                    output = Path(temp)/f'{owner}-{scenario}-{sleep}.json'
                    command = [str(binary), '--owner', owner, '--bodies', str(args.bodies),
                               '--steps', str(args.steps), '--record', str(output)]
                    command += ['--scenario', scenario]
                    if sleep: command += ['--solver', 'chipmunk', '--sleep-after', '.5']
                    print(f'Recording {owner} {scenario}: {"Chipmunk with sleeping" if sleep else "both solvers"}', flush=True)
                    subprocess.run(command, cwd=root, check=True)
                    recordings.extend(json.loads(output.read_text())['recordings'])
    for owner in {r['owner'] for r in recordings}:
        for scene in {r['scene'] for r in recordings if r['owner'] == owner}:
            pair = [r for r in recordings if r['owner'] == owner and r['scene'] == scene and not r['sleepAfter']]
            if {r['solver'] for r in pair} != {'basic', 'chipmunk'}:
                raise RuntimeError('Side-by-side playback requires a build with Chipmunk enabled')
    payload = json.dumps({'version': 1, 'recordings': recordings}, separators=(',', ':')).replace('<', r'\u003c')
    if args.compact:
        payload = base64.b64encode(gzip.compress(payload.encode('utf-8'), mtime=0)).decode('ascii')
    html = (source/'viewer.html').read_text().replace('__PDG_RECORDINGS__', payload)
    html = html.replace('__PDG_RECORDING_TYPE__', 'application/octet-stream' if args.compact else 'application/json')
    html = html.replace('__PDG_RECORDING_ENCODING__', 'gzip-base64' if args.compact else 'json')
    html = html.replace('__PDG_VIEWER_JS__', (source/'viewer.js').read_text())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(html)
    print(f'Open in a browser: {args.output.resolve()}')


if __name__ == '__main__':
    main()
