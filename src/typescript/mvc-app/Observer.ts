import { host } from './host';
import type PDG = require('../../../types');

// -----------------------------------------------
// Observer.ts
//
// TypeScript implementation of the Observer pattern classes
// Subject/IObserver for managing observing changes
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

/**
 * Interface for objects that can observe subjects for changes
 */
export interface Observable {
    addObserver(observer: IObserver): void;
    removeObserver(observer: IObserver): void;
    notifyObservers(): void;
}
class IObserver {


    /**
     * Called when the subject being observed changes
     * @param {Subject} subject - The subject that changed (optional)
     */
    notify(subject: Observable | null = null): void {
        throw new Error("IObserver.notify() must be implemented by subclass");
    }
}

/**
 * Base class for objects that can be observed
 * Manages a list of observers and notifies them when changes occur
 */
class Subject {
    observers: IObserver[];

    constructor() {
        /** @type {IObserver[]} */
        this.observers = [];
    }

    /**
     * Add an observer to be notified of changes
     * @param {IObserver} observer - The observer to add
     */
    addObserver(observer: IObserver): void {
        if (!observer || typeof observer.notify !== 'function') {
            throw new Error("Observer must implement IObserver interface");
        }

        // Check for duplicate adds in debug mode
        if (host.process?.env?.NODE_ENV === 'development') {
            for (const existingObserver of this.observers) {
                if (existingObserver === observer) {
                    console.warn("Subject::addObserver added same observer twice");
                    break;
                }
            }
        }

        this.observers.push(observer);
    }

    /**
     * Remove an observer from the notification list
     * @param {IObserver} observer - The observer to remove
     */
    removeObserver(observer: IObserver): void {
        const index = this.observers.indexOf(observer);
        if (index !== -1) {
            this.observers.splice(index, 1);
        }
    }

    /**
     * Notify all observers of a change
     * Most recently added observers are notified first
     */
    notifyObservers(): void {
        // Notify in reverse order (most recently added first)
        for (let i = this.observers.length - 1; i >= 0; i--) {
            try {
                this.observers[i].notify(this);
            } catch (error) {
                console.error("Error notifying observer:", error);
            }
        }
    }

    /**
     * Get the number of observers
     * @returns {number}
     */
    getObserverCount(): number {
        return this.observers.length;
    }

    /**
     * Check if a specific observer is registered
     * @param {IObserver} observer - The observer to check
     * @returns {boolean}
     */
    hasObserver(observer: IObserver): boolean {
        return this.observers.includes(observer);
    }

    /**
     * Remove all observers
     */
    clearObservers(): void {
        this.observers.length = 0;
    }
}

export {
IObserver,
Subject
};
