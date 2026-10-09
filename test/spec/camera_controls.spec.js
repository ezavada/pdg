describe('Camera controllers and effects', function() {
    if (pdg.hasGraphics) describe('composed output', function() {
        var port,layers,cameras,listeners;
        function camera() {
            var result=new pdg.Camera().setViewport(new pdg.Rect(64,64)).setLocation(32,32);
            cameras.push(result);return result;
        }
        function layer(view,color,rect) {
            var result=pdg.createSpriteLayer(port);layers.push(result);result.setCamera(view);
            var sprite=result.createSprite(),drawing=pdg.createDrawing();
            drawing.addRect(rect || new pdg.Rect(64,64),new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None));
            sprite.createPart('art').setDrawing(drawing);return result;
        }
        beforeEach(function(){
            layers=[];cameras=[];listeners=[];port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));
        });
        afterEach(function(){
            cameras.forEach(function(view){view.cancelSchedule();});
            listeners.forEach(function(listener){if(listener.cancel)listener.cancel();});
            layers.forEach(function(item){pdg.cleanupLayer(item);});pdg.gfx.closeGraphicsPort(port);
        });
        it('fades one composed multi-layer image, including later contents and flashes', function(){
            var view;
            runs(function(){
                view=camera().setOpacity(.5);layer(view,'red',new pdg.Rect(0,0,48,48));
                layer(view,'blue',new pdg.Rect(16,16,48,48));
            });
            waits(80);
            runs(function(){
                var image=new pdg.Image(port),single=image.getPixel(8,8),overlap=image.getPixel(24,24);
                expect(single.alpha).toBeCloseTo(.5,2);expect(single.red).toBeGreaterThan(.95);
                expect(overlap.alpha).toBeCloseTo(.5,2);expect(overlap.blue).toBeGreaterThan(.95);expect(overlap.red).toBeLessThan(.05);
                layer(view,'green',new pdg.Rect(48,0,64,16));view.flash(.5,100,pdg.linearTween).animate(0);view.pauseSchedule();
            });
            waits(80);
            runs(function(){
                var image=new pdg.Image(port),added=image.getPixel(56,8),overlap=image.getPixel(24,24);
                expect(added.alpha).toBeCloseTo(.5,2);expect(added.green).toBeGreaterThan(.7);
                expect(overlap.alpha).toBeCloseTo(.5,2);expect(overlap.red).toBeCloseTo(.5,1);expect(overlap.blue).toBeGreaterThan(.95);
                view.hide();
            });
            waits(80);
            runs(function(){expect(new pdg.Image(port).getPixel(24,24).alpha).toBeLessThan(.01);});
        });
        it('cuts at the scheduled instant without blending or changing either camera opacity',function(){
            var source,destination;
            runs(function(){
                source=camera().setOpacity(.5);destination=camera().setOpacity(.25).hide();layer(source,'red');layer(destination,'blue');
                source.wait(1).cutTo(destination);source.animate(.5);source.pauseSchedule();
            });
            waits(80);
            runs(function(){var pixel=new pdg.Image(port).getPixel(20,20);expect(pixel.red).toBeGreaterThan(.99);expect(pixel.blue).toBeLessThan(.01);expect(pixel.alpha).toBeCloseTo(.5,2);source.resumeSchedule().animate(.5);});
            waits(80);
            runs(function(){var pixel=new pdg.Image(port).getPixel(20,20);expect(pixel.red).toBeLessThan(.01);expect(pixel.blue).toBeGreaterThan(.99);expect(pixel.alpha).toBeCloseTo(.25,2);});
        });
        it('allows pending cuts across different viewports and interleaved camera layers',function(){
            var source,destination;
            runs(function(){
                source=camera();destination=camera().hide().setViewport(new pdg.Rect(8,8,56,56));
                layer(source,'red');layer(camera(),'green',new pdg.Rect(48,48,64,64));layer(source,'white',new pdg.Rect(0,0,8,8));layer(destination,'blue');
                source.wait(1).cutTo(destination);source.animate(.5);source.pauseSchedule();
            });
            waits(80);
            runs(function(){expect(new pdg.Image(port).getPixel(20,20).red).toBeGreaterThan(.99);source.resumeSchedule().animate(.5);});
            waits(80);
            runs(function(){var image=new pdg.Image(port);expect(image.getPixel(20,20).blue).toBeGreaterThan(.99);expect(image.getPixel(60,60).green).toBeGreaterThan(.45);expect(image.getPixel(4,4).alpha).toBeLessThan(.01);});
        });
        it('crossfades live scenes without darkening and preserves screen-space UI', function(){
            var source,destination;
            runs(function(){
                source=camera();destination=camera().hide();
                var first=layer(source,'red');var second=layer(destination,'blue');
                port.setCameraDrawingEnabled(false);
                listeners.push(second.onDrawPortComplete(function(){
                    port.drawRect(new pdg.Rect(48,48,64,64),new pdg.Attributes().fillColor('green').lineStyle(pdg.lineStyle_None));return false;
                }));
                expect(source.transitionTo(destination,2,pdg.camera_Crossfade,pdg.linearTween)).toBe(source);
                source.animate(1);source.pauseSchedule();
                expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(false);
            });
            waits(80);
            runs(function(){
                var image=new pdg.Image(port),pixel=image.getPixel(20,20),hud=image.getPixel(56,56);
                expect(pixel.alpha).toBeGreaterThan(.99);expect(pixel.red).toBeCloseTo(.5,2);expect(pixel.blue).toBeCloseTo(.5,2);
                expect(hud.green).toBeGreaterThan(.45);expect(hud.red).toBeLessThan(.05);expect(hud.blue).toBeLessThan(.05);
                source.setOpacity(.5);destination.setOpacity(.25);
            });
            waits(80);
            runs(function(){
                var pixel=new pdg.Image(port).getPixel(20,20);
                expect(pixel.alpha).toBeCloseTo(.375,2);expect(pixel.red).toBeCloseTo(2/3,2);expect(pixel.blue).toBeCloseTo(1/3,2);
                source.setOpacity(1);destination.setOpacity(1);
                source.resumeSchedule().animate(1);
                expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
            });
            waits(80);
            runs(function(){var pixel=new pdg.Image(port).getPixel(20,20);expect(pixel.red).toBeLessThan(.01);expect(pixel.blue).toBeGreaterThan(.99);});
        });
        it('renders a matched fade after approach and before settling',function(){
            var source,destination;
            runs(function(){
                source=camera();destination=camera().hide();
                var a=layer(source,'red').createSprite().setLocation(32,32).setSize(4,4);
                var b=layer(destination,'blue').createSprite().setLocation(32,32).setSize(4,4);
                source.matchFadeTo(destination,{matchSource:a,matchTarget:b,approachSeconds:.1,fadeSeconds:1,settleSeconds:.1,fadeEasing:pdg.easeInQuad});
                source.animate(.6);source.pauseSchedule();
                expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(false);
            });
            waits(80);
            runs(function(){
                var pixel=new pdg.Image(port).getPixel(20,20);
                expect(pixel.red).toBeCloseTo(.75,2);expect(pixel.blue).toBeCloseTo(.25,2);expect(pixel.alpha).toBeGreaterThan(.99);
                source.resumeSchedule().animate(.5);source.pauseSchedule();expect(source.isHidden()).toBe(true);
            });
            waits(80);
            runs(function(){var pixel=new pdg.Image(port).getPixel(20,20);expect(pixel.blue).toBeGreaterThan(.99);expect(pixel.red).toBeLessThan(.01);});
        });
        it('queues, pauses, cancels and validates crossfade ownership', function(){
            var source=camera(),destination=camera().hide();layer(source,'red');layer(destination,'blue');
            expect(function(){source.transitionTo(source,1);}).toThrow();
            expect(function(){source.transitionTo(destination,-1);}).toThrow();
            expect(function(){source.transitionTo(destination,1,99);}).toThrow();
            source.transitionTo(destination,1).stopIt();
            expect(function(){new pdg.Serializer().serialize_obj(source);}).not.toThrow();
            expect(function(){source.restartIt();}).toThrow();source.cancelSchedule();
            source.wait(.5).transitionTo(destination,1,pdg.camera_Crossfade,pdg.linearTween);
            expect(function(){source.repeat(2);}).toThrow();
            expect(function(){source.reverse();}).toThrow();
            expect(function(){source.until(function(){return true;});}).toThrow();
            source.animate(.25);expect(destination.isHidden()).toBe(true);
            expect(function(){destination.transitionTo(source,1);}).toThrow();
            expect(function(){new pdg.Serializer().serialize_obj(source);}).toThrow();
            source.animate(.5);source.pauseIt().animate(2);expect(destination.isHidden()).toBe(false);expect(source.isHidden()).toBe(false);
            source.cancelSchedule();expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
            source.transitionTo(destination,1).animate(.25);source.stopIt();expect(destination.isHidden()).toBe(true);
            source.cancelSchedule();destination.setViewport(new pdg.Rect(32,32));
            expect(function(){source.transitionTo(destination,1);}).toThrow();
            destination.setViewport(new pdg.Rect(64,64));source.transitionTo(destination,0);
            expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        });
        [
            ['Left',48,20,16,20], ['Right',16,20,48,20],
            ['Up',20,48,20,16], ['Down',20,16,20,48]
        ].forEach(function(direction) {
            it('wipes '+direction[0]+' with exact endpoints, own opacity and viewport clipping', function(){
                var source,destination;
                runs(function(){
                    source=camera().setViewport(new pdg.Rect(8,8,56,56)).setOpacity(.5);
                    destination=camera().setViewport(new pdg.Rect(8,8,56,56)).setOpacity(.25).hide();
                    layer(source,'red');var last=layer(destination,'blue');
                    port.setCameraDrawingEnabled(false);
                    listeners.push(last.onDrawPortComplete(function(){
                        port.drawRect(new pdg.Rect(0,0,8,8),new pdg.Attributes().fillColor('green').lineStyle(pdg.lineStyle_None));return false;
                    }));
                    source.transitionTo(destination,2,pdg['camera_Wipe'+direction[0]],pdg.linearTween);
                    source.animate(0);source.pauseSchedule();
                });
                waits(80);
                runs(function(){
                    var image=new pdg.Image(port),pixel=image.getPixel(32,32);
                    expect(pixel.red).toBeGreaterThan(.99);expect(pixel.blue).toBeLessThan(.01);
                    expect(pixel.alpha).toBeCloseTo(.5,2);
                    source.resumeSchedule().animate(1);source.pauseSchedule();
                });
                waits(80);
                runs(function(){
                    var image=new pdg.Image(port),revealed=image.getPixel(direction[1],direction[2]),remaining=image.getPixel(direction[3],direction[4]);
                    expect(revealed.blue).toBeGreaterThan(.99);expect(revealed.red).toBeLessThan(.01);expect(revealed.alpha).toBeCloseTo(.25,2);
                    expect(remaining.red).toBeGreaterThan(.99);expect(remaining.blue).toBeLessThan(.01);expect(remaining.alpha).toBeCloseTo(.5,2);
                    expect(image.getPixel(60,60).alpha).toBeLessThan(.01);expect(image.getPixel(4,4).green).toBeGreaterThan(.45);
                    // Adjacent pixels on either side of the shared boundary have no gap.
                    [image.getPixel(31,31),image.getPixel(32,32)].forEach(function(pixel){expect(pixel.alpha).toBeGreaterThan(.24);});
                    source.resumeSchedule().animate(1);
                    expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
                });
                waits(80);
                runs(function(){
                    var pixel=new pdg.Image(port).getPixel(32,32);
                    expect(pixel.red).toBeLessThan(.01);expect(pixel.blue).toBeGreaterThan(.99);expect(pixel.alpha).toBeCloseTo(.25,2);
                });
            });
        });
        [false,true].forEach(function(darkFirst) {
            it('freezes a luma mask and respects reveal order and independent opacity '+darkFirst, function(){
                var source,destination,left;
                runs(function(){
                    source=camera().setOpacity(.5);destination=camera().setOpacity(.25).hide();
                    left=layer(source,'white',new pdg.Rect(0,0,32,64));layer(source,'black',new pdg.Rect(32,0,64,64));layer(destination,'blue');
                    expect(source.lumaFadeTo(destination,2,null,0,darkFirst,pdg.linearTween)).toBe(source);
                    source.animate(0);source.pauseSchedule();
                });
                waits(80);
                runs(function(){
                    var image=new pdg.Image(port);expect(image.getPixel(16,20).red).toBeGreaterThan(.99);expect(image.getPixel(48,20).blue).toBeLessThan(.01);
                    left.setCamera(camera().hide()); // Cached mask must survive live source changes.
                    source.resumeSchedule().animate(1);source.pauseSchedule();
                });
                waits(80);
                runs(function(){
                    var image=new pdg.Image(port),revealed=image.getPixel(darkFirst?48:16,20),remaining=image.getPixel(darkFirst?16:48,20);
                    expect(revealed.blue).toBeGreaterThan(.99);expect(revealed.alpha).toBeCloseTo(.25,2);
                    expect(remaining.blue).toBeLessThan(.01);expect(remaining.alpha).toBeCloseTo(darkFirst?0:.5,2);
                    source.resumeSchedule().animate(1);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
                });
                waits(80);
                runs(function(){var image=new pdg.Image(port);expect(image.getPixel(16,20).blue).toBeGreaterThan(.99);expect(image.getPixel(48,20).blue).toBeGreaterThan(.99);});
            });
        });
        it('uses stretched explicit luma masks with softness and exact endpoints',function(){
            var source,destination,maskPort;
            runs(function(){
                maskPort=pdg.gfx.createOffscreenPort(new pdg.Rect(2,1));
                maskPort.drawRect(new pdg.Rect(0,0,1,1),new pdg.Attributes().fillColor('white').lineStyle(pdg.lineStyle_None));
                maskPort.drawRect(new pdg.Rect(1,0,2,1),new pdg.Attributes().fillColor('black').lineStyle(pdg.lineStyle_None));
                source=camera();destination=camera().hide();layer(source,'red');layer(destination,'blue');
                source.lumaFadeTo(destination,2,new pdg.Image(maskPort),1,false,pdg.linearTween).animate(0);source.pauseSchedule();
            });
            waits(80);
            runs(function(){expect(new pdg.Image(port).getPixel(16,20).red).toBeGreaterThan(.99);source.resumeSchedule().animate(.5);source.pauseSchedule();});
            waits(80);
            runs(function(){var image=new pdg.Image(port),pixel=image.getPixel(16,20);expect(pixel.red).toBeCloseTo(.5,2);expect(pixel.blue).toBeCloseTo(.5,2);expect(pixel.alpha).toBeGreaterThan(.99);expect(image.getPixel(48,20).red).toBeGreaterThan(.99);source.resumeSchedule().animate(1.5);pdg.gfx.closeGraphicsPort(maskPort);});
        });
        it('clips translated camera textures without stretching their contents',function(){
            runs(function(){
                var source=camera().setViewport(new pdg.Rect(8,8,56,56)).setOpacity(.5);
                var destination=camera().setViewport(new pdg.Rect(8,8,56,56)).hide();
                layer(source,'red',new pdg.Rect(0,0,32,64));
                layer(source,'blue',new pdg.Rect(32,0,64,64));
                layer(destination,'white');
                // A 22-pixel shift reproduced dropped fragments in the iOS
                // compositor when it submitted the unclipped quad to GL ES.
                source.whipPanTo(destination,2,pdg.camera_WhipRight,0,pdg.linearTween);
                source.animate(22.5/24);source.pauseSchedule();
            });
            waits(80);
            runs(function(){
                var image=new pdg.Image(port),red=image.getPixel(48,20),blue=image.getPixel(55,20);
                expect(red.red).toBeGreaterThan(.99);expect(red.blue).toBeLessThan(.01);
                expect(blue.blue).toBeGreaterThan(.99);expect(blue.red).toBeLessThan(.01);
                expect(red.alpha).toBeCloseTo(.5,2);expect(blue.alpha).toBeCloseTo(.5,2);
                expect(image.getPixel(16,20).alpha).toBeGreaterThan(.99);
                expect(image.getPixel(60,20).alpha).toBeLessThan(.01);
            });
        });
        [['Left',48,20,16,20],['Right',16,20,48,20],['Up',20,48,20,16],['Down',20,16,20,48]].forEach(function(direction){
            [0,1].forEach(function(blur){
                it('whips '+direction[0]+' with blur '+blur+' without changing camera pose or opening edge gaps',function(){
                    var source,destination;
                    runs(function(){
                        source=camera().setViewport(new pdg.Rect(8,8,56,56)).setOpacity(.5);destination=camera().setViewport(new pdg.Rect(8,8,56,56)).setOpacity(.25).hide();
                        layer(source,'red');layer(destination,'blue');
                        expect(source.whipPanTo(destination,2,pdg['camera_Whip'+direction[0]],blur,pdg.linearTween)).toBe(source);
                        source.animate(1);source.pauseSchedule();
                    });
                    waits(80);
                    runs(function(){
                        var image=new pdg.Image(port),revealed=image.getPixel(direction[1],direction[2]),remaining=image.getPixel(direction[3],direction[4]);
                        expect(revealed.blue).toBeGreaterThan(.99);expect(revealed.alpha).toBeCloseTo(.25,2);expect(remaining.red).toBeGreaterThan(.99);expect(remaining.alpha).toBeCloseTo(.5,2);
                        expect(image.getPixel(31,31).alpha).toBeGreaterThan(.24);expect(image.getPixel(32,32).alpha).toBeGreaterThan(.24);expect(image.getPixel(60,60).alpha).toBeLessThan(.01);
                        expect(source.getLocation().x).toBe(32);expect(destination.getLocation().y).toBe(32);
                        source.resumeSchedule().animate(1);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
                    });
                });
            });
        });
        ['black','white','transparent'].forEach(function(color){
            it('forces complete luma endpoints for a uniform '+color+' mask',function(){
                var source,destination,maskPort;
                runs(function(){
                    maskPort=pdg.gfx.createOffscreenPort(new pdg.Rect(1,1));
                    if(color!=='transparent') maskPort.drawRect(new pdg.Rect(1,1),new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None));
                    source=camera();destination=camera().hide();layer(source,'red');layer(destination,'blue');
                    source.lumaFadeTo(destination,2,new pdg.Image(maskPort),0,false,pdg.linearTween);source.animate(0);source.pauseSchedule();
                });
                waits(80);
                runs(function(){expect(new pdg.Image(port).getPixel(20,20).red).toBeGreaterThan(.99);source.resumeSchedule().animate(1);source.pauseSchedule();});
                waits(80);
                runs(function(){var pixel=new pdg.Image(port).getPixel(20,20);expect(color==='white'?pixel.blue:pixel.red).toBeGreaterThan(.99);source.resumeSchedule().animate(1);});
                waits(80);
                runs(function(){expect(new pdg.Image(port).getPixel(20,20).blue).toBeGreaterThan(.99);pdg.gfx.closeGraphicsPort(maskPort);});
            });
        });
        it('translates artwork during a whip rather than only revealing fixed scenes',function(){
            var source,destination;
            runs(function(){
                source=camera();destination=camera().hide();
                layer(source,'red',new pdg.Rect(0,0,32,64));layer(source,'green',new pdg.Rect(32,0,64,64));
                layer(destination,'blue',new pdg.Rect(0,0,32,64));layer(destination,'white',new pdg.Rect(32,0,64,64));
                source.whipPanTo(destination,2,pdg.camera_WhipLeft,0,pdg.linearTween);source.animate(1);source.pauseSchedule();
            });
            waits(80);
            runs(function(){var image=new pdg.Image(port);expect(image.getPixel(16,20).green).toBeGreaterThan(.45);expect(image.getPixel(16,20).red).toBeLessThan(.01);expect(image.getPixel(48,20).blue).toBeGreaterThan(.99);expect(image.getPixel(48,20).red).toBeLessThan(.01);});
        });
        [
            [.325,.25,.375], [.65,0,.375], [1.3,0,.25], [.0001,.5,.5]
        ].forEach(function(sample){
            it('scales whip blur by speed for duration '+sample[0]+' while bounding the exposure',function(){
                var source,destination;
                runs(function(){
                    source=camera();destination=camera().hide();layer(source,'red');layer(destination,'blue');
                    source.whipPanTo(destination,sample[0],pdg.camera_WhipLeft,.7,pdg.linearTween);
                    source.animate(sample[0]/2);source.pauseSchedule();
                });
                waits(80);
                runs(function(){
                    var image=new pdg.Image(port),outer=image.getPixel(35,20),inner=image.getPixel(33,20);
                    expect(outer.red).toBeCloseTo(sample[1],2);expect(inner.red).toBeCloseTo(sample[2],2);
                    expect(outer.alpha).toBeGreaterThan(.99);expect(inner.alpha).toBeGreaterThan(.99);
                    source.resumeSchedule().animate(sample[0]/2);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
                });
            });
        });
        it('validates luma and whip options without reserving camera ownership',function(){
            var source=camera(),destination=camera().hide();layer(source,'red');layer(destination,'blue');
            expect(function(){source.lumaFadeTo(destination,1,null,-1);}).toThrow();expect(function(){source.lumaFadeTo(destination,1,null,NaN);}).toThrow();
            expect(function(){source.whipPanTo(destination,1,pdg.camera_Crossfade);}).toThrow();expect(function(){source.whipPanTo(destination,1,pdg.camera_WhipLeft,2);}).toThrow();
            source.whipPanTo(destination,1).animate(.5);source.pauseSchedule();source.cancelSchedule();expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
            source.resumeSchedule().lumaFadeTo(destination,0);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        });
        it('rejects ambiguous scene ordering and cross-port transitions', function(){
            var source=camera(),other=camera(),destination=camera();
            layer(source,'red');var middle=layer(other,'green');layer(source,'blue');layer(destination,'white');
            expect(function(){source.setOpacity(.5);}).toThrow();
            expect(source.getOpacity()).toBe(1);
            expect(function(){source.transitionTo(destination,1);}).toThrow();
            middle.setCamera(source);
            source.setOpacity(.5);expect(source.getOpacity()).toBe(.5);
            var elsewhere=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64)),foreign=pdg.createSpriteLayer(elsewhere),view=new pdg.Camera();
            try {
                foreign.setCamera(view);expect(function(){source.transitionTo(view,1);}).toThrow();
            } finally {pdg.cleanupLayer(foreign);pdg.gfx.closeGraphicsPort(elsewhere);}
        });
        it('cancels a transition when its destination detaches', function(){
            var source=camera(),destination=camera().hide();layer(source,'red');var target=layer(destination,'blue');
            source.transitionTo(destination,1).animate(.25);expect(destination.isHidden()).toBe(false);
            target.setCamera(null);expect(destination.isHidden()).toBe(true);expect(source.isHidden()).toBe(false);
            source.animate(2);expect(source.isHidden()).toBe(false);source.cancelSchedule();
            var writer=new pdg.Serializer();expect(function(){writer.serialize_obj(source);}).not.toThrow();
            target.setCamera(destination);
            source.wait(.5).transitionTo(destination,1);
            target.setCamera(null);target.setCamera(destination);
            source.wait(1).transitionTo(destination,1);
            source.animate(.75);expect(destination.isHidden()).toBe(true);
            source.animate(.5);expect(destination.isHidden()).toBe(false);
            source.cancelSchedule();expect(destination.isHidden()).toBe(true);
        });
        it('composes direct Port camera drawing and keeps split-screen fades clipped', function(){
            var upper,lower;
            runs(function(){
                upper=camera().setViewport(new pdg.Rect(0,0,64,32)).setOpacity(.5);
                lower=camera().setViewport(new pdg.Rect(0,32,64,64)).setOpacity(.25);
                layer(upper,'red');layer(lower,'blue');
            });
            waits(80);
            runs(function(){
                var image=new pdg.Image(port);
                expect(image.getPixel(20,16).alpha).toBeCloseTo(.5,2);
                expect(image.getPixel(20,48).alpha).toBeCloseTo(.25,2);
                upper.hide();lower.hide();
                port.getCamera().setOpacity(.75);
                listeners.push(layers[1].onDrawPortComplete(function(){
                    port.drawRect(new pdg.Rect(64,64),new pdg.Attributes().fillColor('green').lineStyle(pdg.lineStyle_None));return false;
                }));
            });
            waits(80);
            runs(function(){
                var pixel=new pdg.Image(port).getPixel(20,20);
                expect(pixel.alpha).toBeCloseTo(.75,2);expect(pixel.green).toBeGreaterThan(.45);
                port.getCamera().hide();
            });
            waits(80);
            runs(function(){expect(new pdg.Image(port).getPixel(20,20).alpha).toBeLessThan(.01);});
        });
    });
    it('follows within a deadzone and gives position ownership to manual animation', function() {
        var target=new pdg.Animated(), camera=new pdg.Camera();
        target.setLocation(100,200); expect(camera.follow(target)).toBe(camera); camera.animate(.1);
        expect(camera.getLocation().x).toBe(100); expect(camera.isFollowing()).toBe(true);
        camera.setDeadzone(new pdg.Rect(-10,-10,10,10)); target.setLocation(105,200); camera.animate(.1);
        expect(camera.getLocation().x).toBe(100); target.setLocation(120,200); camera.animate(.1);
        expect(camera.getLocation().x).toBe(110);
        camera.zoomTo(2,.1,pdg.linearTween).animate(.1); expect(camera.isFollowing()).toBe(true);
        camera.moveTo(300,400,.1,pdg.linearTween).animate(.1); expect(camera.isFollowing()).toBe(false);
        expect(camera.getLocation().x).toBe(300);
        expect(function(){camera.follow(camera);}).toThrow();
        var other=new pdg.Camera(); camera.follow(other); expect(function(){other.follow(camera);}).toThrow(); camera.stopFollowing();
    });
    it('smooths and predicts with finite seconds and rejects invalid settings', function() {
        var target=new pdg.Animated(), camera=new pdg.Camera(); target.setLocation(100,0);
        camera.setSmoothing(1).follow(target).animate(1);
        expect(camera.getLocation().x).toBeCloseTo(100*(1-Math.exp(-1)),4);
        camera.stopFollowing().setSmoothing(0).setLocation(0,0).setLookAhead(.5).follow(target);
        target.setLocation(110,0); camera.animate(.1); expect(camera.getLocation().x).toBeCloseTo(160,4);
        expect(function(){camera.setSmoothing(-1);}).toThrow(); expect(function(){camera.setLookAhead(Infinity);}).toThrow();
        expect(function(){camera.setDeadzone(new pdg.Rect(10,0,0,10));}).toThrow();
    });
    it('clamps each viewport footprint and converts coordinates without changing persistent pose', function() {
        var camera=new pdg.Camera(), viewport=new pdg.Rect(0,0,20,20); camera.setViewBounds(new pdg.Rect(0,0,100,100));
        camera.setViewport(viewport); var corner=camera.viewToWorld(new pdg.Point(0,0)); expect(corner.x).toBeCloseTo(0,4); expect(corner.y).toBeCloseTo(0,4);
        camera.setViewport(viewport); var point=new pdg.Point(50,60), restored=camera.viewToWorld(camera.worldToView(point));
        expect(restored.x).toBeCloseTo(50,4); expect(restored.y).toBeCloseTo(60,4); expect(camera.getLocation().x).toBe(0);
        camera.setLocation(1000,1000).setRotation(.4).setZoom(2);
        [new pdg.Point(0,0),new pdg.Point(20,0),new pdg.Point(0,20),new pdg.Point(20,20)].forEach(function(point){
            var world=camera.viewToWorld(point); expect(world.x).toBeGreaterThan(-.001);expect(world.x).toBeLessThan(100.001);
            expect(world.y).toBeGreaterThan(-.001);expect(world.y).toBeLessThan(100.001);
        });
    });
    it('runs ordinary named presets on a transient stage and preserves following', function() {
        var target=new pdg.Animated(), camera=new pdg.Camera(), viewport=new pdg.Rect(0,0,20,20);
        target.setLocation(100,200); camera.follow(target); var effects=camera.getEffects(); expect(camera.getEffects()).toBe(effects);
        effects.playScript('shake'); camera.animate(.025); expect(camera.getLocation().x).toBe(100); expect(camera.isFollowing()).toBe(true);
        expect(camera.worldToView(new pdg.Point(100,200)).x).not.toBe(10);
        camera.animate(.575); expect(effects.getLocation().x).toBeCloseTo(0,5);
        effects.playScript('impulse'); camera.animate(.04); expect(effects.getLocation().y).toBe(-12); camera.animate(.04); expect(effects.getLocation().y).toBe(0);
        camera.flash(1,.25); camera.animate(.125); expect(camera.getFlashOpacity()).toBeGreaterThan(0); camera.animate(.125); expect(camera.getFlashOpacity()).toBe(0);
        expect(typeof new pdg.Animated().flash).toBe('undefined'); expect(function(){effects.getEffects();}).toThrow();
        camera.stopFollowing();
    });
    it('restores controller settings and independent transient playback from snapshots', function() {
        var source=new pdg.Camera(); source.setSmoothing(.2).setLookAhead(.1).setDeadzone(new pdg.Rect(-3,-4,3,4));
        source.setFollowOffset(new pdg.Offset(5,6)).setViewBounds(new pdg.Rect(-100,-100,100,100)); source.getEffects().playScript('shake');source.animate(.025);
        var writer=new pdg.Serializer(); writer.serialize_obj(source); var reader=new pdg.Deserializer(); reader.setDataPtr(writer.getDataPtr());var copy=reader.deserialize_obj();
        expect(copy.getSmoothing()).toBeCloseTo(.2,6); expect(copy.getLookAhead()).toBeCloseTo(.1,6); expect(copy.getDeadzone().left).toBe(-3);
        expect(copy.getFollowOffset().x).toBe(5); expect(copy.hasViewBounds()).toBe(true); expect(copy.getEffects()).not.toBe(source.getEffects());
        copy.animate(.575); expect(copy.getEffects().getLocation().x).toBeCloseTo(0,5);expect(source.getEffects().hasScheduledAnimations()).toBe(true);
        source.follow(new pdg.Animated());expect(function(){new pdg.Serializer().serialize_obj(source);}).toThrow();source.stopFollowing();
    });
    it('keeps zoom completion when composing live scripted zoom groups', function() {
        var camera=new pdg.Camera(), completions=[]; var listener=camera.onZoomComplete(function(event){completions.push(event.zoom);return false;});
        camera.batch().zoomTo(3,.1,pdg.linearTween).andThen().zoom(.5,.1,pdg.linearTween).endBatch().animate(.2);
        expect(completions).toEqual([3,1.5]); camera.zoomTo(2,.1,pdg.linearTween).yoyo().animate(.2);
        expect(completions).toEqual([3,1.5,2]); expect(camera.getZoom()).toBeCloseTo(1.5,5);
        camera.zoomTo(9,1,pdg.linearTween).until(function(){return true;}).animate(0);expect(completions).toEqual([3,1.5,2,1.5]); listener.cancel();
    });
    it('schedules camera-specific flash as one selected operation and restores viewport state', function() {
        var camera=new pdg.Camera();camera.setViewport(new pdg.Rect(0,0,100,50));
        expect(camera.wait(.1).flash(.8,.2,pdg.linearTween)).toBe(camera);
        camera.animate(.05);expect(camera.getFlashOpacity()).toBe(0);
        camera.animate(.15);expect(camera.getFlashOpacity()).toBeCloseTo(.4,5);
        camera.pauseIt().animate(.5);expect(camera.getFlashOpacity()).toBeCloseTo(.4,5);
        var writer=new pdg.Serializer();writer.serialize_obj(camera);var reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());var copy=reader.deserialize_obj();
        expect(copy.getViewport().width()).toBe(100);copy.resumeIt().animate(.1);expect(copy.getFlashOpacity()).toBeCloseTo(0,5);
        expect(typeof camera.changeFlashTo).toBe('undefined');
        expect(typeof pdg.Animated.defineScript('no-flash-method-'+Date.now()).changeFlashTo).toBe('undefined');
        expect(function(){camera.flash(2,1);}).toThrow();
    });
    if (pdg.hasGraphics) it('clips managed top/bottom views and composites each camera flash once at frame end', function() {
        var port,top,bottom,extra,erase;
        runs(function(){
            port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));top=pdg.createSpriteLayer(port);bottom=pdg.createSpriteLayer(port);extra=pdg.createSpriteLayer(port);
            var camera=new pdg.Camera();camera.setViewport(new pdg.Rect(0,0,64,32));top.setCamera(camera);extra.setCamera(camera);
            var lower=new pdg.Camera();lower.setViewport(new pdg.Rect(0,32,64,64));bottom.setCamera(lower);
            [['red',top],['blue',bottom]].forEach(function(entry){var sprite=entry[1].createSprite(),art=pdg.createDrawing();art.addRect(new pdg.Rect(-100,-100,100,100),new pdg.Attributes().fillColor(entry[0]).lineStyle(pdg.lineStyle_None));sprite.createPart('art').setDrawing(art);});
            erase=top.onErasePort(function(){port.clear();return true;});
            camera.flash(.5,100,pdg.linearTween).animate(0);
        });
        waits(80);
        runs(function(){try{
            var image=new pdg.Image(port),upper=image.getPixel(10,10),lower=image.getPixel(10,50);
            expect(upper.red).toBeGreaterThan(.9);expect(upper.green).toBeCloseTo(.5,1);expect(lower.blue).toBeGreaterThan(.9);expect(lower.red).toBeLessThan(.1);
            expect(port.getClipRect().height()).toBe(64);
        }finally{if(erase && erase.cancel)erase.cancel();pdg.cleanupLayer(top);pdg.cleanupLayer(bottom);pdg.cleanupLayer(extra);pdg.gfx.closeGraphicsPort(port);}});
    });
});

if (pdg.hasGraphics) describe('Sprite camera match cuts',function(){
    var port,layers,source,destination,a,b;
    function position(sprite){return (sprite===a?layers[0]:layers[1]).layerToPortPoint(new pdg.Quad(sprite.getRotatedBounds()).centerPoint());}
    function apparentSize(sprite){var q=(sprite===a?layers[0]:layers[1]).layerToPortQuad(new pdg.Quad(sprite.getRotatedBounds()));var bounds=q.getBounds();return Math.max(bounds.width(),bounds.height());}
    function options(extra){var result={matchSource:a,matchTarget:b,mode:pdg.matchTarget,approachSeconds:.4,settleSeconds:.4};Object.keys(extra||{}).forEach(function(key){result[key]=extra[key];});return result;}
    beforeEach(function(){
        port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));layers=[pdg.createSpriteLayer(port),pdg.createSpriteLayer(port)];
        source=new pdg.Camera().setViewport(new pdg.Rect(64,64)).setLocation(32,32);
        destination=new pdg.Camera().setViewport(new pdg.Rect(64,64)).setLocation(32,32).hide();
        layers[0].setCamera(source);layers[1].setCamera(destination);
        a=layers[0].createSprite().setLocation(12,20).setSize(10,10);b=layers[1].createSprite().setLocation(48,40).setSize(20,20);
    });
    afterEach(function(){source.cancelSchedule();destination.cancelSchedule();layers.forEach(function(layer){pdg.cleanupLayer(layer);});pdg.gfx.closeGraphicsPort(port);});
    it('starts a matched fade only after synchronization and reserves through settling',function(){
        source.matchFadeTo(destination,options({mode:pdg.matchSource,fadeSeconds:.3}));source.animate(.399);
        expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        source.animate(.00101);expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(false);
        expect(position(a).x).toBeCloseTo(position(b).x,4);expect(position(a).y).toBeCloseTo(position(b).y,4);
        source.animate(.299);expect(source.isHidden()).toBe(false);
        source.animate(.00101);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        expect(function(){destination.cutTo(source);}).toThrow();source.animate(.4);
        expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('keeps moving subjects and projected size synchronized throughout the fade',function(){
        source.setRotation(.2);destination.setRotation(-.3).flipX();layers[0].setCameraParallax(.7,.8);layers[1].setCameraParallax(.6,.9);
        source.matchFadeTo(destination,options({mode:pdg.matchSourceAndSize,fadeSeconds:.4}));source.animate(.4);
        for(var i=1;i<=8;++i){
            a.setLocation(12+i*2,20+i);b.setLocation(48-i,40-i*2).setScale(1+i*.02,1+i*.02);
            destination.setRotation(-.3+i*.01);source.animate(.049);
            expect(position(a).x).toBeCloseTo(position(b).x,3);expect(position(a).y).toBeCloseTo(position(b).y,3);
            expect(apparentSize(a)).toBeCloseTo(apparentSize(b),3);expect(source.isHidden()).toBe(false);
        }
        source.animate(.00801);expect(source.isHidden()).toBe(true);
    });
    it('carries approach motion through a target-matched fade and into settling',function(){
        source.matchFadeTo(destination,options({mode:pdg.matchTargetAndSize,fadeSeconds:.3}));source.animate(.399);
        var before=position(a),sizeBefore=apparentSize(a);source.animate(.00101);var start=position(a),sizeStart=apparentSize(a);
        source.animate(.001);var next=position(a),sizeNext=apparentSize(a);
        expect(Math.abs((next.x-start.x)-(start.x-before.x))/.001).toBeLessThan(4);
        expect(Math.abs((sizeNext-sizeStart)-(sizeStart-sizeBefore))/.001).toBeLessThan(4);
        for(var i=0;i<5;++i){source.animate(.05);expect(position(a).x).toBeCloseTo(position(b).x,3);expect(apparentSize(a)).toBeCloseTo(apparentSize(b),3);}
        source.animate(.047);var endBefore=position(a);source.animate(.001);var end=position(a);source.animate(.00101);var incoming=position(b);
        expect(source.isHidden()).toBe(true);expect(Math.abs((incoming.x-end.x)/.00101-(end.x-endBefore.x)/.001)).toBeLessThan(5);
    });
    it('pauses and cancels a fade, restoring the original visibility and corrections',function(){
        var originalA=position(a),originalB=position(b);
        source.wait(.1).matchFadeTo(destination,options({mode:pdg.matchSource,fadeSeconds:.3}));source.animate(.55);
        source.pauseSchedule();var synced=position(b);source.animate(1);expect(source.isHidden()).toBe(false);expect(position(b).x).toBeCloseTo(synced.x,4);
        source.cancelSchedule();expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        expect(position(a).x).toBeCloseTo(originalA.x,4);expect(position(b).x).toBeCloseTo(originalB.x,4);
    });
    it('returns to destination framing after fading and settles before chained work',function(){
        var original=position(b);
        source.matchFadeTo(destination,options({mode:pdg.matchSourceAndSize,fadeSeconds:.3,settleReturnsCamera:true})).andThen().zoomTo(2,.2,pdg.linearTween);
        source.animate(1.1);expect(position(b).x).toBeCloseTo(original.x,3);expect(destination.getZoom()).toBeCloseTo(1,4);expect(source.getZoom()).toBeCloseTo(1,4);
        source.animate(.2);expect(source.getZoom()).toBeCloseTo(2,4);expect(destination.isHidden()).toBe(false);
    });
    it('cancels safely if a subject is removed during the fade',function(){
        source.matchFadeTo(destination,options());source.animate(.5);
        layers[0].removeSprite(a);source.animate(.1);
        expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('uses the full sample interval when a moving subject crosses the fade boundary',function(){
        source.matchFadeTo(destination,options({mode:pdg.matchSource,fadeSeconds:.3}));source.animate(.68);
        a.setLocation(15,20);source.animate(.03);
        var before=position(b);source.animate(.001);var after=position(b);
        expect(source.isHidden()).toBe(true);
        expect(Math.abs((after.x-before.x)/.001-100)).toBeLessThan(6);
    });
    it('preserves native pan speed when a frame crosses the fade boundary',function(){
        source.moveBy(100,0,1,pdg.linearTween);
        source.matchFadeTo(destination,options({mode:pdg.matchSource,fadeSeconds:.3}));source.animate(.68);source.animate(.03);
        var before=position(b);source.animate(.001);var after=position(b);
        expect(Math.abs((after.x-before.x)/.001+100)).toBeLessThan(6);
    });
    it('rejects invalid fade durations, easings, and overlapping composition',function(){
        [0,-1,Infinity,null,'1'].forEach(function(value){expect(function(){source.matchFadeTo(destination,options({fadeSeconds:value}));}).toThrow();});
        expect(function(){source.matchFadeTo(destination,options({fadeEasing:99999}));}).toThrow();
        expect(function(){source.matchFadeTo(destination,options({fadeEasing:pdg.easeOutBounce}));}).toThrow();
        var third=pdg.createSpriteLayer(port);third.setCamera(source);
        expect(function(){source.matchFadeTo(destination,options());}).toThrow();pdg.cleanupLayer(third);
    });
    it('uses the source shot as the default reference without moving its framing',function(){
        var settings=options();delete settings.mode;
        var original=position(a),originalSize=apparentSize(a);
        source.matchCutTo(destination,settings);source.animate(.2);
        expect(position(a).x).toBeCloseTo(original.x,4);expect(position(a).y).toBeCloseTo(original.y,4);
        expect(apparentSize(a)).toBeCloseTo(originalSize,4);
        expect(position(b).x).toBeCloseTo(original.x,4);expect(position(b).y).toBeCloseTo(original.y,4);
        expect(apparentSize(b)).toBeCloseTo(20,4);expect(destination.isHidden()).toBe(true);
        source.animate(.2);
        expect(destination.isHidden()).toBe(false);expect(position(b).x).toBeCloseTo(original.x,4);
    });
    [pdg.matchSource,pdg.matchSourceAndSize].forEach(function(mode){
      [false,true].forEach(function(settleReturnsCamera){
       it('inherits a linear source camera animation and settles (mode '+mode+', returns '+settleReturnsCamera+')',function(){
        source.moveBy(16,-8,.8,pdg.linearTween);
        source.matchCutTo(destination,options({mode:mode,settleReturnsCamera:settleReturnsCamera}));source.animate(0);
        function step(dt){source.animate(dt);}
        for(var i=0;i<398;++i)step(.001);
        var p0=position(a);step(.001);var p1=position(a);
        step(.001001);var p2=position(b),atCut=position(a);step(.001);var p3=position(b);
        expect(destination.isHidden()).toBe(false);
        expect(source.getLocation().x).toBeCloseTo(32+20*.401001,3);
        expect(p2.x).toBeCloseTo(atCut.x,3);expect(p2.y).toBeCloseTo(atCut.y,3);
        expect(Math.abs((p3.x-p2.x)/.001+20)).toBeLessThan(.5);
        expect(Math.abs((p3.y-p2.y)/.001-10)).toBeLessThan(.5);
        expect(Math.abs((p3.x-p2.x)-(p1.x-p0.x))/.001).toBeLessThan(.5);
        step(.398);var nearRest=position(b);step(.001);
        expect(position(b).x).toBeCloseTo(nearRest.x,3);expect(position(b).y).toBeCloseTo(nearRest.y,3);
        if(settleReturnsCamera) {
            expect(position(b).x).toBeCloseTo(48,3);expect(position(b).y).toBeCloseTo(40,3);
        }
       });
      });
    });
    it('uses the target shot as reference while the visible source approaches it',function(){
        var original=position(a),target=position(b),targetSize=apparentSize(b);
        source.matchCutTo(destination,options({mode:pdg.matchTargetAndSize}));source.animate(.2);
        expect(position(a).x).toBeGreaterThan(original.x);expect(position(a).x).toBeLessThan(target.x);
        expect(position(b).x).toBeCloseTo(target.x,4);expect(position(b).y).toBeCloseTo(target.y,4);
        expect(apparentSize(b)).toBeCloseTo(targetSize,4);expect(destination.isHidden()).toBe(true);
        source.animate(.1999);expect(position(a).x).toBeCloseTo(target.x,1);
        expect(apparentSize(a)).toBeCloseTo(targetSize,1);
    });
    it('approaches target framing and cuts at the approach boundary, then completes settling',function(){
        expect(source.matchCutTo(destination,options())).toBe(source);source.animate(.3999);
        var before=position(a);expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        source.animate(.00010001);var after=position(b);
        expect(after.x).toBeCloseTo(before.x,1);expect(after.y).toBeCloseTo(before.y,1);
        expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        expect(function(){destination.cutTo(source);}).toThrow();source.animate(.40000001);
        expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('preserves apparent motion across the handoff and eases it to rest',function(){
        source.matchCutTo(destination,options());source.animate(.3998);var p0=position(a);source.animate(.0001);var p1=position(a);
        source.animate(.0001);var p2=position(b);source.animate(.0001);var p3=position(b);
        expect((p3.x-p2.x)/.0001).toBeCloseTo((p1.x-p0.x)/.0001,0);
        expect((p3.y-p2.y)/.0001).toBeCloseTo((p1.y-p0.y)/.0001,0);
        source.animate(.3998);var finalBefore=position(b);source.animate(.0001);var finalAfter=position(b);
        expect(finalAfter.x).toBeCloseTo(finalBefore.x,3);expect(finalAfter.y).toBeCloseTo(finalBefore.y,3);
    });
    it('matches hidden target position and size through rotated parallax views',function(){
        source.setRotation(.3).setZoom(1.3);destination.setRotation(-.4).flipX();layers[0].setCameraParallax(.5,.7);layers[1].setCameraParallax(.8,.6);
        var original=position(a),originalSize=apparentSize(a);
        source.matchCutTo(destination,options({mode:pdg.matchSourceAndSize}));source.animate(.4);
        expect(position(b).x).toBeCloseTo(original.x,3);expect(position(b).y).toBeCloseTo(original.y,3);expect(apparentSize(b)).toBeCloseTo(originalSize,3);
        source.animate(.4);expect(position(b).x).toBeCloseTo(original.x,3);expect(position(b).y).toBeCloseTo(original.y,3);
        expect(apparentSize(b)).toBeCloseTo(originalSize,3);expect(destination.getZoom()).not.toBe(1);
    });
    it('returns to the original destination framing and zoom only when requested',function(){
        var original=position(b),size=apparentSize(b);
        source.matchCutTo(destination,options({mode:pdg.matchSourceAndSize,settleReturnsCamera:true}));source.animate(.4);
        expect(position(b).x).toBeCloseTo(position(a).x,3);source.animate(.4);
        expect(position(b).x).toBeCloseTo(original.x,3);expect(position(b).y).toBeCloseTo(original.y,3);expect(apparentSize(b)).toBeCloseTo(size,3);expect(destination.getZoom()).toBeCloseTo(1,5);
    });
    it('queues, pauses and cancels safely before and after the cut',function(){
        var original=position(a);source.wait(.2).matchCutTo(destination,options());source.animate(.1);
        expect(position(a).x).toBe(original.x);source.pauseSchedule().animate(1);expect(destination.isHidden()).toBe(true);
        source.resumeSchedule().animate(.3);expect(destination.isHidden()).toBe(true);source.cancelSchedule();expect(position(a).x).toBe(original.x);
        source.matchCutTo(destination,options({mode:pdg.matchSource}));source.animate(.4);var matched=position(b);
        source.cancelSchedule();expect(destination.isHidden()).toBe(false);expect(source.isHidden()).toBe(true);expect(position(b).x).toBeCloseTo(matched.x,4);
    });
    it('freezes approach and settling corrections when paused',function(){
        source.matchCutTo(destination,options());source.animate(.2);source.pauseSchedule();
        var fixed=position(a);b.setLocation(60,50);source.animate(.1);expect(position(a).x).toBeCloseTo(fixed.x,4);
        source.resumeSchedule().animate(.2);source.pauseSchedule();fixed=position(b);source.animate(1);expect(position(b).x).toBeCloseTo(fixed.x,4);
        source.resumeSchedule().animate(.4);expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('cancels safely when an active subject changes cameras',function(){
        source.matchCutTo(destination,options());source.animate(.2);layers[0].setCamera(destination);source.animate(.1);
        expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('preserves following and returns toward its live view',function(){
        destination.follow(b);destination.animate(0);
        source.matchCutTo(destination,options({mode:pdg.matchSource,settleReturnsCamera:true}));source.animate(.4);
        b.setLocation(60,50);destination.animate(.1);source.animate(.4);
        expect(destination.isFollowing()).toBe(true);expect(destination.getLocation().x).toBe(60);expect(position(b).x).toBeCloseTo(32,4);
    });
    it('compensates moving subjects while matching size and size velocity',function(){
        source.matchCutTo(destination,options({mode:pdg.matchTargetAndSize}));source.animate(0);
        var time=0;
        function move(dt){time+=dt;a.setLocation(12+15*time,20-5*time);b.setLocation(48-10*time,40+8*time);}
        for(var i=0;i<398;++i){move(.001);source.animate(.001);}
        var p0=position(a),s0=apparentSize(a);
        move(.001);source.animate(.001);var p1=position(a),s1=apparentSize(a);
        move(.001);source.animate(.001001);var p2=position(b),s2=apparentSize(b);
        move(.001);source.animate(.001);var p3=position(b),s3=apparentSize(b);
        expect(Math.abs((p3.x-p2.x)-(p1.x-p0.x))/.001).toBeLessThan(3);
        expect(Math.abs((p3.y-p2.y)-(p1.y-p0.y))/.001).toBeLessThan(3);
        expect(Math.abs((s3-s2)-(s1-s0))/.001).toBeLessThan(3);
    });
    it('finishes both phases in a large tick and starts chained work afterward',function(){
        source.matchCutTo(destination,options({mode:pdg.matchSource})).andThen().zoomTo(2,.2,pdg.linearTween);
        source.animate(1);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);expect(source.getZoom()).toBeCloseTo(2,5);
        expect(function(){destination.cutTo(source);}).not.toThrow();
    });
    it('compensates ongoing incoming camera rotation and zoom',function(){
        source.matchCutTo(destination,options({mode:pdg.matchSourceAndSize}));source.animate(0);
        var time=0;
        function step(dt){time+=dt;destination.setRotation(time*.8).setZoom(1+time*.3);source.animate(dt);}
        for(var i=0;i<399;++i)step(.001);
        step(.001001);var before=position(b),sizeBefore=apparentSize(b);step(.001);var after=position(b);
        expect(Math.abs(after.x-before.x)/.001).toBeLessThan(2);
        expect(Math.abs(after.y-before.y)/.001).toBeLessThan(2);
        expect(Math.abs(apparentSize(b)-sizeBefore)/.001).toBeLessThan(2);
    });
    it('matches a following source using its current target position',function(){
        source.follow(a);source.animate(0);source.matchCutTo(destination,options());
        source.animate(.3);a.setLocation(18,24);source.animate(.1);
        expect(source.isFollowing()).toBe(true);expect(position(a).x).toBeCloseTo(position(b).x,3);expect(position(a).y).toBeCloseTo(position(b).y,3);
    });
    it('retains the matched following offset and permits snapshots after completion',function(){
        destination.follow(b);destination.animate(0);source.matchCutTo(destination,options({mode:pdg.matchSource}));source.animate(.8);
        var matched=position(b);b.setLocation(60,50);destination.animate(.1);
        expect(destination.isFollowing()).toBe(true);expect(position(b).x).toBeCloseTo(matched.x,3);expect(position(b).y).toBeCloseTo(matched.y,3);
        expect(function(){new pdg.Serializer().serialize_obj(source);}).not.toThrow();
        var writer=new pdg.Serializer();writer.serialize_obj(source);var reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());expect(function(){reader.deserialize_obj();}).not.toThrow();
    });
    it('rejects invalid options and uncontrollable matching',function(){
        [{mode:'wrong'},{mode:-1},{mode:4},{mode:1.5},{mode:NaN},{mode:Infinity},{mode:null},{mode:true},{approachSeconds:0},{settleSeconds:-1},{settleReturnsCamera:1},{approachEasing:pdg.easeOutBounce},{settleEasing:99999},{matchSource:b}].forEach(function(extra){expect(function(){source.matchCutTo(destination,options(extra));}).toThrow();});
        expect(function(){source.matchCutTo(a,options());}).toThrow();
        expect(function(){source.matchCutTo(destination,options({matchSource:source}));}).toThrow();
        var bad=options();Object.defineProperty(bad,'mode',{get:function(){throw Error('bad option');}});
        expect(function(){source.matchCutTo(destination,bad);}).toThrow();
        layers[0].setCameraParallax(0,1);expect(function(){source.matchCutTo(destination,options());}).toThrow();
    });
    it('cancels if a matched Sprite is removed and rejects pending snapshots',function(){
        source.matchCutTo(destination,options());expect(function(){new pdg.Serializer().serialize_obj(source);}).toThrow();
        layers[0].removeSprite(a);source.animate(.1);expect(destination.isHidden()).toBe(true);expect(function(){destination.cutTo(source);}).not.toThrow();
    });
});
