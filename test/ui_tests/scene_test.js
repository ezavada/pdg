// test/ui scene --wait: T toggles gameplay; Space pauses the visual harness.
(function() {
    'use strict';
    var session=pdg.visualTestSession;
    var interactive=!!session || process.argv.indexOf('--wait')>=0;
    var port=pdg.gfx.getMainPort() || pdg.gfx.createWindowPort(new pdg.Rect(960,640),'Scenes: HUD over gameplay');
    if(!port)throw new Error('Scene UI test needs a window');
    var area=port.getDrawingArea(),width=area.width(),height=area.height();
    var game=new pdg.Scene(),hud=new pdg.Scene();
    game.setFixedStep(1/60);game.setInterpolation(true);
    var world=game.createSpriteLayer(),overlay=hud.createSpriteLayer();
    world.setSpritePort(port);overlay.setSpritePort(port);
    world.setUseChipmunkPhysics(true);overlay.setUseChipmunkPhysics(false);
    game.getCamera().setViewport(area).setLocation(width/2,height/2);
    hud.getCamera().setViewport(area).setLocation(width/2,height/2);
    port.setCameraDrawingEnabled(false);
    function attrs(color){return new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None);}
    function art(layer,drawing,x,y){var s=layer.createSprite();s.createPart('art').setDrawing(drawing);s.setLocation(x,y);return s;}
    var backdrop=pdg.createDrawing();
    backdrop.addRect(new pdg.Rect(0,0,width,height),attrs('#142438'));
    for(var i=0;i<15;++i){
        var x=width*i/15;
        backdrop.addRect(new pdg.Rect(x,height*.25,x+width/30,height*.8),attrs('#34465e'));
    }
    art(world,backdrop,0,0);
    var box=pdg.createDrawing();box.addRect(new pdg.Rect(-30,-30,30,30),attrs('#fbac62'));
    // The moving gameplay sprite passes behind the translucent HUD panel.
    var player=art(world,box,width*.15,height*.58);player.setupPhysicsBody().setVelocity(new pdg.Vector(width*.08,0));
    player.physics.setAngularVelocity(.7);
    var panelArt=pdg.createDrawing();
    panelArt.addRect(new pdg.Rect(20,height*.4,width-20,height*.72),attrs(new pdg.Color(.035,.07,.11,.78)));
    art(overlay,panelArt,0,0);
    var spinnerArt=pdg.createDrawing();spinnerArt.addRect(new pdg.Rect(-40,-7,40,7),attrs('#65edd4'));
    spinnerArt.addEllipse(new pdg.Point(33,0),11,11,attrs('#ffffff'));
    var spinner=art(overlay,spinnerArt,width*.85,height*.56);spinner.setSpin(2);
    var caretArt=pdg.createDrawing();caretArt.addRect(new pdg.Rect(-2,-14,2,14),attrs('#65edd4'));
    var caret=art(overlay,caretArt,width*.73,height*.56);var caretOn=true;
    var gameTimers=0,hudTimers=0,pausedPosition=null,pausedAngle=0,pauseHudAngle=0,pausedTicks=0,resumedTicks=0,done=false;
    var pauseGameTimers=0,pauseHudTimers=0;
    game.onInterval(function(){++gameTimers;},200);
    hud.onInterval(function(){++hudTimers;caretOn=!caretOn;caret.setOpacity(caretOn?1:0);},250);
    function toggle(){
        if(game.isPaused()){game.resume();game.setInputEnabled(true);}
        else {game.pause();game.setInputEnabled(false);pausedPosition=player.getLocation();pausedAngle=player.getRotation();pauseHudAngle=spinner.getRotation();pauseGameTimers=gameTimers;pauseHudTimers=hudTimers;}
    }
    var phase=0;
    hud.onInterval(function(){
        if(done)return;
        if(!game.isPaused() && player.getLocation().x>width*.85)player.setLocation(width*.15,height*.58);
        if(game.isPaused() && pausedPosition){
            if(Math.abs(player.getLocation().x-pausedPosition.x)>.001 || Math.abs(player.getRotation()-pausedAngle)>.001)throw new Error('Gameplay moved while scene paused');
            if(gameTimers!==pauseGameTimers)throw new Error('Gameplay timer fired while scene paused');
            ++pausedTicks;
        } else if(phase>=2)++resumedTicks;
        ++phase;
        if(phase===8)toggle();
        if(phase===20){
            if(Math.abs(spinner.getRotation()-pauseHudAngle)<.1)throw new Error('HUD spinner failed to advance during gameplay pause');
            if(hudTimers<=pauseHudTimers)throw new Error('HUD timer failed to advance during gameplay pause');
            toggle();
        }
        if(phase===32 && !interactive){
            if(pausedTicks<10 || resumedTicks<10 || !gameTimers || hudTimers<20)throw new Error('Scene UI phases failed');
            console.log('SCENE UI PASS: gameplay froze/resumed; HUD spinner, caret and timers continued');finish();
        }
        if(interactive && phase>=32)phase=0;
    },200);
    if(session)session.onPause.push(function(paused){if(paused){game.pause();hud.pause();}else{game.resume();hud.resume();}});
    overlay.onPostDrawLayer(function(){
        port.drawText('GAMEPLAY '+(game.isPaused()?'PAUSED':'RUNNING'),new pdg.Point(40,height*.47),attrs('#ffffff').textSize(24));
        port.drawText('HUD timer '+hudTimers+'  |  caret',new pdg.Point(40,height*.59),attrs('#65edd4').textSize(18));
        port.drawText('Gameplay timer '+gameTimers+'  |  T: pause/resume',new pdg.Point(40,height*.68),attrs('#b5c7dc').textSize(16));
        if(session)session.draw(port);return true;
    });
    pdg.on(pdg.eventType_PortDraw,function(){return false;});
    pdg.onKeyPress(function(event){if(event.unicode===84||event.unicode===116){toggle();return true;}if(!session && event.unicode===pdg.key_Escape){finish();return true;}return false;});
    function finish(){if(done)return;done=true;game.dispose();hud.dispose();pdg.gfx.closeGraphicsPort(port);pdg.quit();}
    pdg.run();
}());
