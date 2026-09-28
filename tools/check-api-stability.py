#!/usr/bin/env python3
"""Check class-note coverage and shared ratings; optionally inspect generated pages."""
import argparse
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parent.parent
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--site', type=Path, help='Generated site containing cxx/ and javascript/')
args = parser.parse_args()
ratings = {}
for language in ('cxx', 'javascript'):
    source = root / 'docs' / language / 'dox' / 'api-stability.dox'
    entries = re.findall(r'\\(?:class|struct) pdg::(\w+)\s+\\note \*\*API Stability: ([123])', source.read_text())
    assert len(entries) == len(dict(entries)), f'{language}: duplicate class ratings'
    ratings[language] = dict(entries)
    # All class ratings live in one file; old warning/precondition notes must not survive.
    for other in source.parent.glob('*.dox'):
        if other != source:
            assert 'API Stability:' not in other.read_text(), f'Duplicate policy in {other}'
    if args.site:
        html = args.site / language / 'html'
        # Doxygen sometimes inlines class details into a topic/namespace page.
        index = (html / 'annotated.html').read_text()
        for name in ratings[language]:
            encoded = re.sub(r'[A-Z]', lambda match: '_' + match[0].lower(), name)
            compound = '(?:class|struct)pdg_1_1' + encoded
            found = re.search(r'href="([^"#]*(?:' + compound + r')[^"#]*\.html)(?:#[^"]*)?"', index)
            if not found:
                found = re.search(r'href="([^"#]+\.html)#' + compound + r'"', index)
            assert found, f'{language}: {name} is absent from the class index'
            page = (html / found[1]).read_text()
            assert 'API Stability:' in page and 'api_stability' in page, f'{language}: missing rendered note/link for {name}'
    print(f'{language}: {len(entries)} class ratings checked')
exposed = json.loads((root / 'docs/javascript/pdg-js.json').read_text())['interface']
classes = {entry['name'] for entry in exposed if entry['type'] == 'class'}
assert classes <= ratings['javascript'].keys(), 'Unrated JavaScript classes: ' + ', '.join(sorted(classes - ratings['javascript'].keys()))
for name, level in ratings['javascript'].items():
    native = name + 'T' if name in ('Point', 'Offset', 'Vector', 'Rect', 'Quad', 'RotatedRect') else name
    if native in ratings['cxx']:
        assert ratings['cxx'][native] == level, f'Language mismatch: {name}'
print('Exposed JavaScript coverage and shared-language ratings match')
