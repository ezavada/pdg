// -----------------------------------------------
// eventemitter.spec.js
//
// test suite for EventEmitter
//
// Written by Ed Zavada, 2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

describe("EventEmitter", function() {

  it("can be created with no params", function() {
	console.log('* Testing EventEmitter...');
  	var emitter = new pdg.EventEmitter();
  });
  
  it("can be assigned handlers", function() {
  	var handler = new pdg.IEventHandler(function() {});
  	var handler_all = new pdg.IEventHandler(function() {});
  	var emitter = new pdg.EventEmitter();
	expect(pdg.all_events).toEqual(0);
	expect(pdg.eventType_Timer).not.toEqual(pdg.all_events);
	expect(pdg.eventType_Shutdown).not.toEqual(pdg.all_events);
	expect(pdg.eventType_KeyDown).not.toEqual(pdg.all_events);
	expect(pdg.eventType_Shutdown).not.toEqual(pdg.eventType_Timer);
	expect(pdg.eventType_KeyDown).not.toEqual(pdg.eventType_Timer);
	expect(pdg.eventType_Shutdown).not.toEqual(pdg.eventType_KeyDown);
  	emitter.addHandler(handler);
  	emitter.addHandler(handler_all, pdg.all_events);
  });

  describe("adding/removing handlers", function() {

	var handler;
	var handler_all;
	var emitter;
	
    beforeEach(function() {
		handler = new pdg.IEventHandler(function() { return false; });
		handler_all = new pdg.IEventHandler(function() { return false; });
		emitter = new pdg.EventEmitter();
		emitter.addHandler(handler, pdg.eventType_Timer);
		emitter.addHandler(handler_all, pdg.all_events);
    });

	  it("can add same handler for multiple events", function() {
		emitter.addHandler(handler, pdg.eventType_Shutdown);
		emitter.addHandler(handler, pdg.eventType_KeyDown);
	  });

	if (typeof process === 'undefined') {
	// built-in gives debug assert in standalone
 	  it("can have same handler added twice for same event", function() {
 		emitter.addHandler(handler, pdg.eventType_Timer);
 	  });
	}

	  it("can have handlers removed", function() {
	  	emitter.removeHandler(handler, pdg.eventType_Timer);
	  	emitter.removeHandler(handler_all, pdg.all_events);
	  });

	  it("can have same handler removed multiple times", function() {
	  	emitter.removeHandler(handler_all);
	  	emitter.removeHandler(handler_all);
	  	emitter.removeHandler(handler_all, pdg.all_events);
	  });

	if (typeof process === 'undefined') {
	  // built-in emits warning to debug log through C++, no way for javascript to see it
	  it("warns on remove handler from event it never handled", function() {
    	spyOn(pdg, 'warn');
	  	emitter.removeHandler(handler, pdg.eventType_Shutdown);
	  	expect(pdg.warn).toHaveBeenCalledWith("EventEmitter::removeHandler could not find inType 2 [2] in mHandlers");
	  });
	}
  });
  
if (typeof process === 'undefined') {
	// none of these can be tested with this test spec because
	// EventEmitter.postEvent() is not exposed by the built-in
	// pdg framework

  describe("event dispatching", function() {

	var handler_t1;
	var handler_t2;
	var handler_s1;
	var emitter;
	
	
    beforeEach(function() {
		this.testCallback1 = function(event) {
			console.log("got event "+event);
			return false;
		}
		this.testCallback2 = function(event) {
			console.log("got event "+event);
			return false;
		}
		this.testCallback3 = function(event) {
			console.log("got event "+event);
			return event.return_val;
		}
	  	spyOn(this, 'testCallback1').andReturn(false);
	  	spyOn(this, 'testCallback2').andReturn(false);
	  	spyOn(this, 'testCallback3').andCallThrough();
		handler_t1 = new pdg.IEventHandler(this.testCallback1);
		handler_t2 = new pdg.IEventHandler(this.testCallback2);
		handler_s1 = new pdg.IEventHandler(this.testCallback3);
		emitter = new pdg.EventEmitter();
		emitter.addHandler(handler_t1, pdg.eventType_Timer);
		emitter.addHandler(handler_t2, pdg.eventType_Timer);
		emitter.addHandler(handler_s1, pdg.eventType_Shutdown);
    });

	  it("sends events to only to correct type handlers", function() {
	  	emitter.postEvent(pdg.eventType_Timer, {id: 1});
	  	expect(this.testCallback1).toHaveBeenCalled();
	  	expect(this.testCallback2).toHaveBeenCalled();
	  	expect(this.testCallback3).not.toHaveBeenCalled();
	  });

	  it("stops sending events once they are handled", function() {
	  	spyOn(handler_t1, 'handleEvent').andReturn(true);
	  	emitter.postEvent(pdg.eventType_Timer, {id: 1});
	  	expect(handler_t1.handleEvent).toHaveBeenCalled();
	  	expect(this.testCallback2).not.toHaveBeenCalled();
	  });

	  it("requires true or false return from handler", function() {
	  	expect(function() { 
	  		emitter.postEvent(pdg.eventType_Shutdown, {return_val: 23});
	  	}).toThrow();
	  	expect(this.testCallback3).toHaveBeenCalled();
	  });

  });

  describe("all_event handlers", function() {

	var handler_1;
	var handler_2;
	var handler_t;
	var emitter;
	
    beforeEach(function() {
		handler_1 = new pdg.IEventHandler(function() { return false; });
		handler_2 = new pdg.IEventHandler(function() { return false; });
		handler_t = new pdg.IEventHandler(function() { return false; });
		emitter = new pdg.EventEmitter();
		emitter.addHandler(handler_t, pdg.eventType_Timer);
		emitter.addHandler(handler_1, pdg.all_events);
		emitter.addHandler(handler_2, pdg.all_events);
    });

	  it("sends unhandled events to any all_events handlers", function() {
	  	spyOn(handler_t, 'handleEvent').andReturn(false);
	  	spyOn(handler_1, 'handleEvent').andReturn(false);
	  	spyOn(handler_2, 'handleEvent').andReturn(true);
	  	emitter.postEvent(pdg.eventType_Timer, {id: 1});
	  	expect(handler_t.handleEvent).toHaveBeenCalled();
	  	expect(handler_1.handleEvent).toHaveBeenCalled();
	  	expect(handler_2.handleEvent).toHaveBeenCalled();
	  });

	  it("stops sending events once they are handled", function() {
	  	spyOn(handler_t, 'handleEvent').andReturn(false);
	  	spyOn(handler_1, 'handleEvent').andReturn(true);
	  	spyOn(handler_2, 'handleEvent');
	  	emitter.postEvent(pdg.eventType_Timer, {id: 1});
	  	expect(handler_t.handleEvent).toHaveBeenCalled();
	  	expect(handler_1.handleEvent).toHaveBeenCalled();
	  	expect(handler_2.handleEvent).not.toHaveBeenCalled();
	  });

	  it("gives specific handlers priority over all_events handlers", function() {
	  	spyOn(handler_t, 'handleEvent').andReturn(false);
	  	spyOn(handler_1, 'handleEvent').andReturn(false);
	  	spyOn(handler_2, 'handleEvent').andReturn(false);
		handler_timer = new pdg.IEventHandler(function() { return false; });
		emitter.addHandler(handler_timer, pdg.eventType_Timer);
	  	spyOn(handler_timer, 'handleEvent').andReturn(true);
	  	emitter.postEvent(pdg.eventType_Timer, {id: 1});
	  	expect(handler_1.handleEvent).not.toHaveBeenCalled();
	  	expect(handler_2.handleEvent).not.toHaveBeenCalled();
	  	expect(handler_t.handleEvent).toHaveBeenCalled();
	  	expect(handler_timer.handleEvent).toHaveBeenCalled();
	  });

  });

}

});