/** Optional diagnostics without installing or declaring ambient Node globals. */
export const host = globalThis as {
    process?: { env?: { NODE_ENV?: string } };
    PDG_CONTROL_DRAW_DIAGNOSTICS?: boolean | { maxSamples?: number; maxDrawsPerButton?: number };
};
