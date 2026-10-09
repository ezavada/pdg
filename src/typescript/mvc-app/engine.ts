import type PDG = require('../../../types');
import type { ControlStateAttributes } from './ControlAttributes';

/** MVC-facing input records, not a complete engine event declaration set. */
export interface MouseInfo {
    mousePos: PDG.Point;
    rightButton?: boolean;
    lastClickElapsed?: number;
    trackingRef?: number;
}
export interface KeyInfo { key?: string; keyCode?: number; unicode?: number; }
export interface WheelInfo { vertDelta: number; horizDelta: number; }
export interface PortInfo { port: PDG.Port; frameNum: number; }
export interface TimerInfo { id: number; }
export type UIEvent = MouseInfo | KeyInfo | WheelInfo | PortInfo | TimerInfo | PDG.Event;
export type EventHandler = PDG.EventSubscription;
export type MVCEventManager = PDG.EventManager;
export type DrawRoutine = (port: PDG.Port, area: PDG.Rect, state: ControlStateAttributes) => void;
export type MVCRuntime = typeof PDG;
const runtime = (globalThis as {pdg?: unknown}).pdg;
if (!runtime || typeof runtime !== 'object') throw new Error('Initialize PDG before loading its TypeScript MVC implementation');
export const engine = runtime as MVCRuntime;
