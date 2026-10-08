import type pdg = require('../../../types');

/** Animate an existing sprite; native construction is deferred in the IDL. */
export function pulse(sprite: pdg.Sprite): pdg.Sprite {
    return sprite.moveTo(160, 120, 0.4).yoyo().repeat(2);
}

/** Narrow nullable lookups before using the returned native instance. */
export function handLocation(sprite: pdg.Sprite): pdg.Point | null {
    const hand = sprite.findPart('hand');
    return hand ? hand.getLocation() : null;
}
