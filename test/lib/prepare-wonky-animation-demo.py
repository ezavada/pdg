#!/usr/bin/env python3
"""Build the fixed-hierarchy Idle/Walk demo asset without modifying the sample.

Run from any directory: python3 test/lib/prepare-wonky-animation-demo.py
The original Walk-only debug point/box tracks are omitted. Attack's intermittent
blur and Crumble's changing hierarchy remain available in the original sample.
Image paths reuse the original PNGs; no artwork is duplicated.
"""
from pathlib import Path
import xml.etree.ElementTree as ET

test_dir = Path(__file__).resolve().parents[1]
source = test_dir / "data/spriter-samples/wonkyskeleton/wonkyskeleton.scml"
destination = test_dir / "data/animation-demo/wonkyskeleton.scml"
tree = ET.parse(source)
root = tree.getroot()
for image in root.findall("folder/file"):
    image.set("name", "../spriter-samples/wonkyskeleton/" + image.get("name"))
omitted_tracks = {"head_point", "hand_collider", "blur_0"}
for entity in root.findall("entity"):
    for info in list(entity.findall("obj_info")):
        if info.get("name") in omitted_tracks:
            entity.remove(info)
    for animation in list(entity.findall("animation")):
        if animation.get("name") not in {"Idle", "Walk"}:
            entity.remove(animation)
            continue
        omitted_ids = set()
        for timeline in list(animation.findall("timeline")):
            if timeline.get("name") in omitted_tracks:
                omitted_ids.add(timeline.get("id"))
                animation.remove(timeline)
        for key in animation.findall("mainline/key"):
            for reference in list(key):
                if reference.get("timeline") in omitted_ids:
                    key.remove(reference)
destination.parent.mkdir(parents=True, exist_ok=True)
ET.indent(tree, space="    ")
tree.write(destination, encoding="UTF-8", xml_declaration=True)
print(destination)
