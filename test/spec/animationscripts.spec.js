describe('Shared animation scripts', function() {
  var sequence=0;
  function script(name,build) {
    var definition=pdg.Animated.defineScript(name); build(definition); definition.endScript(); return name;
  }
  it('shares static definitions and deletes them without cancelling published executions', function() {
    var name='spec-delete-'+(++sequence);
    var definition=pdg.Sprite.defineScript(name).moveBy(10,0,1,pdg.linearTween).endScript();
    var target=new pdg.Animated(); target.playScript(name).animate(.25);
    expect(pdg.Troupe.deleteScript(name)).toBe(true);
    expect(pdg.Camera.deleteScript(name)).toBe(false);
    expect(function(){target.playScript(name);}).toThrow();
    expect(function(){definition.moveBy(1,0,1);}).toThrow();
    expect(function(){definition.endScript();}).toThrow();
    pdg.Camera.defineScript(name).moveBy(20,0,1,pdg.linearTween).endScript();
    target.animate(.75); expect(target.getLocation().x).toBeCloseTo(10,5);
    var replacement=new pdg.Animated(); replacement.playScript(name).animate(1);
    expect(replacement.getLocation().x).toBeCloseTo(20,5);
    expect(pdg.Animated.deleteScript(name)).toBe(true);
    expect(function(){pdg.Animated.deleteScript('');}).toThrow();
    expect(function(){pdg.Animated.deleteScript(123);}).toThrow();
  });
  it('delivers ordered script lifecycle notifications after publishing state', function() {
    var events=[], name='spec-events-'+(++sequence), definition=pdg.Animated.defineScript(name);
    function record(event) { events.push(event.type); expect(event.scriptName).toBe(name); }
    definition.series().mark('home').moveBy(10,0,.1,pdg.linearTween).yoyo().repeat(2).endSeries()
      .onMark(function(event){expect(event.markName).toBe('home');record(event);})
      .onYoyo(function(event){expect(event.reverse).toBe(true);record(event);})
      .onRepeat(function(event){expect(event.iteration).toBeGreaterThan(0);record(event);}).endScript();
    var target=new pdg.Animated(), finished=0, started=0, named=0;
    target.playScript(name).onFinished(function(event) {
      expect(event.target).toBe(target); expect(event.scriptName).toBe(name);
      expect(target.getLocation().x).toBeCloseTo(0,5); ++finished;
      target.moveBy(0,5);
    }).onStarted(function(event){expect(event.target).toBe(target);++started;})
      .onScriptFinished(function(event){expect(event.scriptName).toBe(name);++named;});
    expect(events.length).toBe(0); target.animate(.6);
    expect(events).toEqual(['mark','yoyo','repeat','yoyo','repeat','yoyo']);
    expect(finished).toBe(1); expect(target.getLocation().y).toBeCloseTo(5,5);
    expect(started).toBe(1); expect(named).toBe(1);
    target.animate(.1); expect(finished).toBe(1);
  });
  it('distinguishes until interruptions from natural completion and supports Sprite handlers', function() {
    var blocked=false, calls=0, finished=0, target=new pdg.Animated();
    target.moveBy(10,0,1,pdg.linearTween).andAlso().rotateBy(1,1,pdg.linearTween)
      .until(function(){return blocked;}).onUntilFired(function(event) {
        expect(event.target).toBe(target); expect(event.elapsedSeconds).toBeCloseTo(.25,5); ++calls;
      }).onFinished(function(){++finished;});
    target.animate(.25); blocked=true; target.animate(.25); target.animate(1);
    expect(calls).toBe(1); expect(finished).toBe(1);
    var natural=new pdg.Animated();
    natural.moveBy(1,0,.1).until(function(){return false;}).onUntilFired(function(){++calls;}).animate(.2);
    expect(calls).toBe(1);
    var sprite=new pdg.Sprite(), spriteDone=0;
    expect(sprite.moveBy(1,0,.1).onFinished(function(event){expect(event.target).toBe(sprite);++spriteDone;})).toBe(sprite);
    if(typeof sprite.animate==='function') { sprite.animate(.1);expect(spriteDone).toBe(1); }
    expect(function(){natural.on('',function(){});}).toThrow();
  });
  it('fires custom script events at their step and reserves PDG event names', function() {
    var name='spec-custom-'+(++sequence), calls=0, target=new pdg.Animated();
    pdg.Animated.defineScript(name).series().moveBy(10,0,.1,pdg.linearTween)
      .triggerEvent('arrived').moveBy(10,0,.1,pdg.linearTween).endSeries().repeat(1).endScript();
    target.playScript(name).on('arrived',function(event) {
      expect(event.type).toBe('arrived'); expect(event.target).toBe(target);
      expect(event.scriptName).toBe(name); ++calls;
    });
    expect(calls).toBe(0); target.animate(.05); expect(calls).toBe(0);
    target.animate(.05); expect(calls).toBe(1); target.animate(.3); expect(calls).toBe(2);
    var live=new pdg.Animated(), immediate=0;
    live.moveBy(1,0,1).on('signal',function(){++immediate;});
    expect(live.triggerEvent('signal')).toBe(live); expect(immediate).toBe(1);
    live.animate(.1); live.triggerEvent('signal'); expect(immediate).toBe(2);
    ['started','finished','scriptFinished','mark','yoyo','repeat','untilFired','eventType_MouseDown','',123].forEach(function(event) {
      expect(function(){live.triggerEvent(event);}).toThrow();
    });
  });
  it('notifies once for staggered Troupe completion', function() {
    var troupe=new pdg.Troupe().add(new pdg.Animated()).add(new pdg.Animated()), calls=0;
    troupe.moveBy(10,0,.2).stagger(.1).onFinished(function(event) {
      expect(event.target).toBe(troupe); ++calls;
    });
    troupe.animate(.2); expect(calls).toBe(0); troupe.animate(.1); expect(calls).toBe(1);
  });
  it('rejects portable callback snapshots and does not replay a failing handler', function() {
    var target=new pdg.Animated(), calls=0;
    target.moveBy(1,0,.1).on('finished',function(){++calls;throw new Error('handler failed');});
    expect(function(){new pdg.Serializer().serialize_obj(target);}).toThrow();
    expect(function(){target.animate(.1);}).toThrow();
    target.animate(.1); expect(calls).toBe(1);
  });
  it('keeps vertical movement outside a blocked horizontal andAlso chain', function() {
    var blocked=false, target=new pdg.Animated();
    target.moveBy(0,100,4,pdg.linearTween).moveBy(100,0,2,pdg.linearTween)
      .andAlso().rotateBy(Math.PI,2,pdg.linearTween).until(function(){return blocked;});
    target.animate(.5); blocked=true; target.animate(.5);
    expect(target.getLocation().x).toBeCloseTo(25,5);
    expect(target.getLocation().y).toBeCloseTo(25,5);
    expect(target.getRotation()).toBeCloseTo(Math.PI/4,5);
    target.animate(3); expect(target.getLocation().y).toBeCloseTo(100,5);
    var recorded=new pdg.Animated(); blocked=false;
    recorded.batch().moveBy(0,100,4,pdg.linearTween).moveBy(100,0,2,pdg.linearTween)
      .andAlso().rotateBy(1,2,pdg.linearTween).until(function(){return blocked;}).endBatch();
    recorded.animate(.5); blocked=true; recorded.animate(.5);
    expect(recorded.getLocation().x).toBeCloseTo(25,5);
    expect(recorded.getLocation().y).toBeCloseTo(25,5);
    var immediate=new pdg.Animated();
    immediate.moveBy(0,100).moveBy(100,0,2).andAlso().rotateBy(1,2).until(function(){return true;});
    immediate.animate(.5); expect(immediate.getLocation().y).toBeCloseTo(100,5);
  });
  it('joins an andAlso chain inside a series and terminates both operations', function() {
    var done=false, target=new pdg.Animated();
    target.series().moveBy(10,0,1,pdg.linearTween).andAlso().rotateBy(1,2,pdg.linearTween)
      .until(function(){return done;}).moveBy(5,0,.2,pdg.linearTween).endSeries();
    target.animate(.5);
    expect(target.getLocation().x).toBeCloseTo(5,5); expect(target.getRotation()).toBeCloseTo(.25,5);
    done=true; target.animate(.2);
    expect(target.getLocation().x).toBeCloseTo(10,5); expect(target.getRotation()).toBeCloseTo(.25,5);
  });
  it('restores visited marks and jumps forward to unvisited marks', function() {
    var name=script('spec-marks-'+(++sequence),function(builder) {
      builder.series().moveBy(10,0,.2,pdg.linearTween).mark('home').moveBy(20,0,.4,pdg.linearTween).endSeries();
    });
    var target=new pdg.Animated(); target.playScript(name).animate(.4);
    expect(target.getLocation().x).toBeCloseTo(20,5);
    expect(target.jumpToMark('home')).toBe(target); expect(target.getLocation().x).toBeCloseTo(10,5);
    target.animate(.2); expect(target.getLocation().x).toBeCloseTo(20,5);
    var forward=new pdg.Animated(); forward.playScript(name).jumpToMark('home').animate(.4);
    expect(forward.getLocation().x).toBeCloseTo(20,5);
  });
  it('animates nested Troupes, Parts and AnimatedAttributes without duplicate targets', function() {
    var first=new pdg.Animated(), second=new pdg.AnimatedAttributes(), sprite=new pdg.Sprite();
    var part=sprite.createPart('troupe-member'), inner=new pdg.Troupe(), outer=new pdg.Troupe();
    first.setLocation(100,0); second.setLocation(200,0);
    expect(inner.add(first)).toBe(inner); outer.add(inner).add(first).add(second).add(part).add(sprite);
    expect(outer.contains(first)).toBe(true); expect(outer.getMemberCount()).toBe(5);
    expect(function(){inner.add(outer);}).toThrow();
    outer.series().moveBy(10,0,.2,pdg.linearTween).rotateBy(1,.2,pdg.linearTween).endSeries();
    outer.animate(.2);
    expect(first.getLocation().x).toBeCloseTo(110,5); expect(second.getLocation().x).toBeCloseTo(210,5);
    expect(part.getLocation().x).toBeCloseTo(10,5); expect(sprite.getLocation().x).toBeCloseTo(10,5);
    first.animate(.2); expect(first.getLocation().x).toBeCloseTo(110,5);
    outer.animate(.1); expect(first.getRotation()).toBeCloseTo(.5,5);
    outer.remove(second); outer.animate(.1); expect(second.getRotation()).toBeCloseTo(.5,5);
    expect(outer.clear()).toBe(outer); expect(outer.getMemberCount()).toBe(0);
  });
  it('staggers a whole batch and joins after the last Troupe member', function() {
    var first=new pdg.Animated(), second=new pdg.Animated(), troupe=new pdg.Troupe();
    troupe.add(first).add(second).batch().moveBy(10,0,.2,pdg.linearTween).rotateBy(1,.2,pdg.linearTween)
      .endBatch().stagger(.1).andThen().moveBy(5,0,.1,pdg.linearTween);
    troupe.animate(.1); expect(first.getLocation().x).toBeCloseTo(5,5); expect(second.getLocation().x).toBeCloseTo(0,5);
    expect(first.getRotation()).toBeCloseTo(.5,5); expect(second.getRotation()).toBeCloseTo(0,5);
    troupe.animate(.15); expect(first.getLocation().x).toBeCloseTo(10,5); expect(second.getLocation().x).toBeCloseTo(7.5,5);
    troupe.animate(.15); expect(first.getLocation().x).toBeCloseTo(15,5); expect(second.getLocation().x).toBeCloseTo(15,5);
    var single=new pdg.Animated(); single.moveBy(10,0,.2,pdg.linearTween).stagger(.1).animate(.2);
    expect(single.getLocation().x).toBeCloseTo(10,5);
  });
  it('records without executing and creates independent native playback instances', function() {
    var name='spec-shake-'+(++sequence), definition=pdg.Animated.defineScript(name);
    expect(definition.moveBy(10,0,.1,pdg.linearTween).yoyo().repeat(2).diminish(0,.6)).toBe(definition);
    expect(function(){definition.getLocation();}).toThrow(); definition.endScript();
    var first=new pdg.Animated(), second=new pdg.Animated();
    first.setLocation(100,0).playScript(name); second.setLocation(200,0).playScript(name);
    first.animate(.1); second.animate(.1);
    expect(first.getLocation().x).toBeCloseTo(108.333333,4);
    expect(second.getLocation().x).toBeCloseTo(208.333333,4);
    first.animate(.5); second.animate(.5);
    expect(first.getLocation().x).toBe(100); expect(second.getLocation().x).toBe(200);
    expect(first.hasScheduledAnimations()).toBe(false);
    expect(function(){definition.moveBy(1,0,1);}).toThrow();
  });
  it('combines group dependencies and accumulated delays across a large update', function() {
    var name=script('spec-sequence-'+(++sequence),function(builder) {
      builder.batch().wait(.1).wait(.1).moveBy(10,0,.2,pdg.linearTween)
        .andThen().wait(.1).moveBy(20,0,.2,pdg.linearTween).endBatch();
    });
    var target=new pdg.Animated(); target.playScript(name).animate(.7);
    expect(target.getLocation().x).toBeCloseTo(30,5);
  });
  it('evaluates a conditional at activation and reverses the branch actually taken', function() {
    var calls=0, name=script('spec-condition-'+(++sequence),function(builder) {
      builder.when(function(context) { ++calls; expect(context.elapsedSeconds).toBe(0); return context.target.getLocation().x<50; })
        .moveBy(10,0,.2,pdg.linearTween).otherwise().moveBy(-10,0,.2,pdg.linearTween).endOtherwise().yoyo();
    });
    expect(calls).toBe(0);
    var target=new pdg.Animated(); target.setLocation(100,0).playScript(name).animate(.2);
    expect(target.getLocation().x).toBe(90); target.animate(.2);
    expect(target.getLocation().x).toBe(100); expect(calls).toBe(1);
  });
  it('terminates at the current sample and releases a dependent operation in the same update', function() {
    var finish=false, name=script('spec-until-'+(++sequence),function(builder) {
      builder.moveBy(100,0,10,pdg.linearTween).until(function(context){return finish;})
        .andThen().moveBy(5,0,.1,pdg.linearTween);
    });
    var target=new pdg.Animated(); target.playScript(name).animate(1); expect(target.getLocation().x).toBe(10);
    finish=true; target.animate(.1); expect(target.getLocation().x).toBe(15);
  });
  it('pauses and restarts the selected invocation using its captured baseline', function() {
    var name=script('spec-controls-'+(++sequence),function(builder){builder.moveBy(10,0,1,pdg.linearTween);});
    var target=new pdg.Animated(); target.setLocation(100,0).playScript(name).animate(.2);
    target.pauseIt().animate(.5); expect(target.getLocation().x).toBeCloseTo(102,5);
    target.resumeIt().animate(.3); expect(target.getLocation().x).toBeCloseTo(105,5);
    target.stopIt().animate(1); expect(target.getLocation().x).toBeCloseTo(105,5);
    target.restartIt(); expect(target.getLocation().x).toBe(100);
    target.animate(1); expect(target.getLocation().x).toBe(110);
  });
  it('increases displacement around the captured baseline and restores its envelope', function() {
    var name=script('spec-increase-'+(++sequence),function(builder){
      expect(builder.moveBy(10,0,1,pdg.linearTween).increase(3,1)).toBe(builder);
    });
    var target=new pdg.Animated(); target.setLocation(100,0).playScript(name).animate(.5);
    expect(target.getLocation().x).toBeCloseTo(110,5);
    var writer=new pdg.Serializer(); writer.serialize_obj(target);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); var copy=reader.deserialize_obj();
    copy.animate(.5); target.animate(.5);
    expect(copy.getLocation().x).toBeCloseTo(130,5);
    expect(target.getLocation().x).toBeCloseTo(130,5);
    var immediate=new pdg.Animated(); immediate.moveBy(10,0,1,pdg.linearTween).increase(2,0).animate(1);
    expect(immediate.getLocation().x).toBeCloseTo(20,5);
    expect(function(){new pdg.Animated().moveBy(1,0,1).increase(.5,1);}).toThrow();
    expect(function(){new pdg.Animated().moveBy(1,0,1).increase(Infinity,1);}).toThrow();
  });
  it('integrates speed envelopes independently of frame partitioning', function() {
    var name=script('spec-rate-'+(++sequence),function(builder){builder.moveBy(100,0,3,pdg.linearTween).speedUp(2,1);});
    var whole=new pdg.Animated(), split=new pdg.Animated(); whole.playScript(name); split.playScript(name);
    whole.animate(1); for(var i=0;i<10;++i) split.animate(.1);
    expect(whole.getLocation().x).toBeCloseTo(50,5); expect(split.getLocation().x).toBeCloseTo(50,5);
  });
  it('restores native playback cursor and baselines through snapshots', function() {
    var name=script('spec-snapshot-'+(++sequence),function(builder){builder.moveBy(10,0,.2,pdg.linearTween).yoyo().repeat(2).diminish(0,1.2);});
    var target=new pdg.Animated(); target.setLocation(100,0).playScript(name).animate(.3);
    [pdg.serialization_Complete,pdg.serialization_ExternalReferences].forEach(function(mode){
      var writer=new pdg.Serializer(); writer.setResourceMode(mode); writer.serialize_obj(target);
      var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); var copy=reader.deserialize_obj();
      expect(copy.getLocation().x).toBeCloseTo(target.getLocation().x,5);
      copy.animate(.9); expect(copy.getLocation().x).toBeCloseTo(100,5);
      expect(target.hasScheduledAnimations()).toBe(true);
    });
  });
  it('restores custom event steps and allows receivers to subscribe or ignore them', function() {
    var eventName='arrived-\u2603', name=script('spec-event-snapshot-'+(++sequence),function(builder) {
      builder.series().moveBy(10,0,.2,pdg.linearTween).triggerEvent(eventName)
        .moveBy(10,0,.2,pdg.linearTween).endSeries().repeat(1);
    });
    [pdg.serialization_Complete,pdg.serialization_ExternalReferences].forEach(function(mode) {
      var target=new pdg.Animated(); target.playScript(name).animate(.1);
      function snapshot(value) {
        var writer=new pdg.Serializer(); writer.setResourceMode(mode); writer.serialize_obj(value);
        var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); return reader.deserialize_obj();
      }
      var receiver=snapshot(target), calls=0;
      receiver.on(eventName,function(event){expect(event.type).toBe(eventName);++calls;});
      receiver.animate(.05); expect(calls).toBe(0);
      receiver.animate(.05); expect(calls).toBe(1);
      receiver.animate(.6); expect(calls).toBe(2); expect(receiver.getLocation().x).toBeCloseTo(20,5);
      var unhandled=snapshot(target); unhandled.animate(.8);
      expect(unhandled.getLocation().x).toBeCloseTo(20,5);
      target.animate(.15); // The first event has already fired without a handler.
      var after=snapshot(target), later=0;
      after.on(eventName,function(){++later;}); after.animate(.05); expect(later).toBe(0);
      after.animate(.5); expect(later).toBe(1); expect(after.getLocation().x).toBeCloseTo(20,5);
    });
    var pending=new pdg.Animated(); pending.series().triggerEvent(eventName).endSeries();
    var writer=new pdg.Serializer(); writer.serialize_obj(pending);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); var draft=reader.deserialize_obj(), fired=0;
    draft.on(eventName,function(){++fired;}).animate(.1); expect(fired).toBe(1);
  });
  it('restores saved marks, pending marks, and ordinary tracks for jumpToMark', function() {
    function snapshot(target) {
      var writer=new pdg.Serializer(); writer.setResourceMode(pdg.serialization_Complete); writer.serialize_obj(target);
      var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); return reader.deserialize_obj();
    }
    var name=script('spec-mark-snapshot-'+(++sequence),function(builder) {
      builder.series().moveBy(10,0,.2,pdg.linearTween).mark('home')
        .moveBy(20,0,.4,pdg.linearTween).endSeries();
    });
    var target=new pdg.Animated();
    target.moveBy(0,100,2,pdg.linearTween).playScript(name).animate(.3);
    var copy=snapshot(target); copy.setLocation(999,999); copy.jumpToMark('home');
    expect(copy.getLocation().x).toBeCloseTo(10,5); expect(copy.getLocation().y).toBeCloseTo(10,5);
    copy.animate(.2); expect(copy.getLocation().x).toBeCloseTo(20,5); expect(copy.getLocation().y).toBeCloseTo(20,5);
    copy=snapshot(copy); copy.jumpToMark('home').animate(.4); expect(copy.getLocation().x).toBeCloseTo(30,5);
    var pending=new pdg.Animated().playScript(name), unsaved=snapshot(pending);
    unsaved.setLocation(50,0).jumpToMark('home',true).animate(.4);
    expect(unsaved.getLocation().x).toBeCloseTo(70,5);
    var noRestore=snapshot(target); noRestore.setLocation(50,0).jumpToMark('home',false).animate(.4);
    expect(noRestore.getLocation().x).toBeCloseTo(70,5);
  });
  it('serializes nested Troupes with shared members and resumes collective playback', function() {
    var a=new pdg.Animated(), b=new pdg.Animated(); a.setLocation(100,0); b.setLocation(200,0);
    var inner=new pdg.Troupe().add(a), outer=new pdg.Troupe().add(inner).add(a).add(b);
    outer.series().mark('home').moveBy(10,0,1,pdg.linearTween).endSeries().animate(.4);
    var writer=new pdg.Serializer(); writer.serialize_obj(a); writer.serialize_obj(outer); writer.serialize_obj(inner); writer.serialize_obj(b); writer.serialize_obj(a); writer.serialize_obj(outer);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr());
    var ca=reader.deserialize_obj(), troupe=reader.deserialize_obj(), nested=reader.deserialize_obj(), cb=reader.deserialize_obj();
    expect(reader.deserialize_obj()).toBe(ca); expect(reader.deserialize_obj()).toBe(troupe);
    expect(troupe instanceof pdg.Troupe).toBe(true); expect(nested instanceof pdg.Troupe).toBe(true);
    expect(troupe.getMemberCount()).toBe(3); expect(troupe.contains(ca)).toBe(true); expect(nested.contains(ca)).toBe(true); expect(troupe.contains(cb)).toBe(true);
    troupe.animate(.6); expect(ca.getLocation().x).toBeCloseTo(110,5); expect(cb.getLocation().x).toBeCloseTo(210,5);
    troupe.jumpToMark('home'); expect(ca.getLocation().x).toBeCloseTo(100,5); expect(cb.getLocation().x).toBeCloseTo(200,5);
    troupe.animate(1); expect(ca.getLocation().x).toBeCloseTo(110,5); expect(cb.getLocation().x).toBeCloseTo(210,5);
    troupe.restartIt().animate(.2); ca.setLocation(500,0); troupe.animate(.8);
    expect(ca.getLocation().x).toBeCloseTo(500,5); expect(cb.getLocation().x).toBeCloseTo(210,5);
    var isolated=new pdg.Troupe().add(new pdg.Animated());
    writer=new pdg.Serializer(); writer.serialize_obj(isolated); reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr());
    var restored=reader.deserialize_obj(); expect(restored.getMemberCount()).toBe(1); restored.moveBy(1,0,.1).animate(.1);
  });
  it('shares Sprite identities between full layer records and Troupe records in either order', function() {
    [false,true].forEach(function(troupeFirst) {
      var layer=pdg.createSpriteLayer(), sprite=layer.createSprite(), troupe=new pdg.Troupe().add(sprite);
      layer.setSerializationFlags(pdg.ser_Full); sprite.setLocation(10,20);
      var writer=new pdg.Serializer();
      if(troupeFirst) writer.serialize_obj(troupe);
      layer.serialize(writer);
      if(!troupeFirst) writer.serialize_obj(troupe);
      writer.serialize_obj(sprite);
      var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); var copy=pdg.createSpriteLayer(), group;
      if(troupeFirst) group=reader.deserialize_obj();
      copy.deserialize(reader);
      if(!troupeFirst) group=reader.deserialize_obj();
      var member=reader.deserialize_obj();
      expect(group.contains(member)).toBe(true); expect(group.contains(copy.getNthSprite(0))).toBe(true);
      group.moveBy(10,0,.1,pdg.linearTween).animate(.1);
      expect(member.getLocation().x).toBeCloseTo(20,5); expect(copy.getNthSprite(0).getLocation().x).toBeCloseTo(20,5);
      pdg.cleanupLayer(layer); pdg.cleanupLayer(copy);
    });
  });
  it('preserves pending Troupe integration so restored members do not advance twice', function() {
    var member=new pdg.Animated(), group=new pdg.Troupe().add(member);
    group.changeMovementTo(10,0,1,pdg.linearTween).animate(.5);
    var writer=new pdg.Serializer(); writer.serialize_obj(group); writer.serialize_obj(member);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr());
    var restored=reader.deserialize_obj(), target=reader.deserialize_obj();
    expect(target.getLocation().x).toBeCloseTo(1.25,5);
    target.animate(.5); expect(target.getLocation().x).toBeCloseTo(1.25,5);
    restored.animate(.5); target.animate(.5); expect(target.getLocation().x).toBeCloseTo(5,5);
  });
  it('restores Troupe Part members through the shared Sprite snapshot', function() {
    var sprite=new pdg.Sprite(), part=sprite.createPart('hand'), id=part.getId(), group=new pdg.Troupe().add(part);
    part.setLocation(3,4); group.moveBy(10,0,1,pdg.linearTween).animate(.4);
    var writer=new pdg.Serializer(); writer.serialize_obj(group); writer.serialize_obj(sprite);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr());
    var restored=reader.deserialize_obj(), copy=reader.deserialize_obj(), hand=copy.getPart(id);
    expect(restored.contains(hand)).toBe(true); expect(hand.getLocation().x).toBeCloseTo(7,5);
    restored.animate(.6); expect(hand.getLocation().x).toBeCloseTo(13,5);
  });
  it('supports late dependencies and snapshots with pending placement', function() {
    var name=script('spec-late-'+(++sequence),function(builder){builder.moveBy(10,0,.5,pdg.linearTween);});
    var target=new pdg.Animated(); target.playScript(name).animate(.2); target.andThen().wait(.1);
    var writer=new pdg.Serializer(); writer.serialize_obj(target);
    var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr()); var copy=reader.deserialize_obj();
    copy.moveBy(20,0,.5,pdg.linearTween).animate(.9);
    expect(copy.getLocation().x).toBeCloseTo(30,5);
    target.animate(.3); target.moveBy(20,0,.5,pdg.linearTween).animate(.6);
    expect(target.getLocation().x).toBeCloseTo(30,5);
    expect(function(){target.repeat(.5);}).toThrow();
  });
  it('restores pending dependencies before the first publication boundary', function() {
    var name=script('spec-unpublished-'+(++sequence),function(builder){builder.moveBy(10,0,.5,pdg.linearTween);});
    var target=new pdg.Animated(); target.playScript(name).andThen().wait(.1);
    var writer=new pdg.Serializer();writer.serialize_obj(target);var reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());var copy=reader.deserialize_obj();
    copy.moveBy(20,0,.5,pdg.linearTween).animate(1.1);expect(copy.getLocation().x).toBeCloseTo(30,5);
  });
  it('defers fluent appearance commands and runs them on the script clock', function() {
    var attributes=new pdg.AnimatedAttributes(), before=attributes.getFillOpacity();
    attributes.series().changeFillOpacity(.2,1,pdg.linearTween).lineThickness(3).endSeries();
    expect(attributes.getFillOpacity()).toBe(before);
    expect(attributes.getLineThickness()).toBe(1);
    attributes.animate(.5);expect(attributes.getFillOpacity()).toBeCloseTo((before+.2)/2,5);
    expect(attributes.getLineThickness()).toBe(1);
    attributes.animate(.5);expect(attributes.getFillOpacity()).toBeCloseTo(.2,5);
    expect(attributes.getLineThickness()).toBe(3);
    var particle=new pdg.Particle().setLifetime(10);particle.series().fadeTo(.2,1,pdg.linearTween).moveBy(10,0,1,pdg.linearTween).endSeries();
    expect(particle.getOpacity()).toBe(1);
    particle.animate(.5);expect(particle.getOpacity()).toBeCloseTo(.6,5);expect(particle.getLocation().x).toBe(0);
    particle.animate(1);expect(particle.getOpacity()).toBeCloseTo(.2,5);expect(particle.getLocation().x).toBeCloseTo(5,5);
  });
  it('records named appearance commands with copied colors and portable arguments', function() {
    var color=new pdg.Color('red'), name=script('spec-appearance-'+(++sequence),function(builder) {
      expect(builder.series().fillColor(color).changeFillOpacity(.2,1,pdg.linearTween).lineThickness(3).endSeries()).toBe(builder);
    });
    color.red=0;
    var target=new pdg.AnimatedAttributes(), before=target.getFillOpacity();
    target.playScript(name);
    expect(target.getFillOpacity()).toBe(before);
    target.animate(.5);
    expect(target.getFillOpacity()).toBeCloseTo((before+.2)/2,5);
    expect(target.getFillColor().red).toBe(1);
    expect(target.getLineThickness()).toBe(1);
    target.animate(.5);expect(target.getFillOpacity()).toBeCloseTo(.2,5);expect(target.getLineThickness()).toBe(3);
    pdg.Animated.deleteScript(name);
  });
  it('records collective appearance operations and rejects invalid inputs before graph edits', function() {
    var a=new pdg.AnimatedAttributes(),b=new pdg.AnimatedAttributes(),troupe=new pdg.Troupe().add(a).add(b);
    expect(function(){troupe.changeFillOpacity('bad',1);}).toThrow();
    expect(function(){troupe.changeFillOpacity(.2,1,-1);}).toThrow();
    expect(troupe.fillColor('blue').changeFillOpacity(.2,1)).toBe(troupe);
    expect(a.getFillOpacity()).toBe(1);troupe.animate(1);
    expect(a.getFillOpacity()).toBeCloseTo(.2,5);expect(b.getFillOpacity()).toBeCloseTo(.2,5);
    expect(a.getFillColor().blue).toBe(1);expect(b.getFillColor().blue).toBe(1);
  });
  it('exposes named frame commands and preserves unsupported-target behavior', function() {
    var name=script('spec-frame-command-'+(++sequence),function(builder){builder.setFrame(0).fadeTo(.25,1);});
    var sprite=new pdg.Sprite(),troupe=new pdg.Troupe().add(sprite);troupe.playScript(name).animate(1);expect(sprite.getOpacity()).toBeCloseTo(.25,5);
    var camera=new pdg.Camera();camera.playScript(name).animate(.5);
    var writer=new pdg.Serializer();writer.serialize_obj(camera);
    var reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());var copy=reader.deserialize_obj();
    copy.animate(.5);expect(copy.getOpacity()).toBeCloseTo(.25,5);
    var unsupported=0,target=new pdg.Animated();
    target.playScript(name).on('unsupportedOp',function(){++unsupported;}).animate(1);
    expect(unsupported).toBe(2);
    pdg.Animated.deleteScript(name);
  });
  it('rejects evaluator snapshots and callback failures explicitly', function() {
    var name=script('spec-error-'+(++sequence),function(builder){builder.when(function(){throw new Error('script failed');}).moveBy(10,0,1).endWhen();});
    var target=new pdg.Animated(); target.playScript(name);
    expect(function(){new pdg.Serializer().serialize_obj(target);}).toThrow();
    expect(function(){target.animate(.1);}).toThrow(); target.animate(1);
    expect(target.getLocation().x).toBe(0);
  });
  it('uses each original playback receiver in a shared evaluator contract', function() {
    var seen=[], name=script('spec-evaluator-owners-'+(++sequence),function(builder) {
      builder.when(function(context){seen.push(context.target);return true;})
        .moveBy(2,0,.1,pdg.linearTween).endWhen();
    });
    var first=new pdg.Animated(), second=new pdg.AnimatedAttributes();
    first.playScript(name).animate(.1); second.playScript(name).animate(.1);
    expect(seen.length).toBe(2); expect(seen[0]).toBe(first); expect(seen[1]).toBe(second);
    [function(){return 1;}, function(){return Promise.resolve(true);}].forEach(function(evaluate) {
      var target=new pdg.Animated();
      target.when(evaluate).moveBy(1,0,.1).endWhen();
      expect(function(){target.animate(.1);}).toThrow();
      expect(target.getLocation().x).toBe(0);
    });
  });
  if (typeof document !== 'undefined') it('converts easing types and applies IDL defaults without per-method adapters', function() {
    ['diminish','increase','slowDown','speedUp'].forEach(function(method) {
      var target=new pdg.Animated(); target.moveBy(10,0,1,pdg.linearTween);
      expect(target[method](1,1)).toBe(target);
      [-1,256,NaN,Infinity,.5,null,'0'].forEach(function(easing) {
        expect(function(){target[method](1,1,easing);}).toThrow();
      });
      target.animate(1); expect(target.getLocation().x).toBeCloseTo(10,5);
    });
  });
});
