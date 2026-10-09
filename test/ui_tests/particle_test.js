// Whole-body particles, optional physics, and particles with their own emitters.
const port = pdg.gfx.createWindowPort(new pdg.Rect(40, 40, 940, 660), 'Particle effects');
const layer = pdg.createSpriteLayer(port);
// Keep the normal PortDraw event visible to the UI test harness.
pdg.on(pdg.eventType_PortDraw, function() { return false; });
layer.setMaxParticles(1500);
if (layer.setGravity) layer.setGravity(100);

function disc(color) {
    const drawing = pdg.createDrawing();
    drawing.addEllipse(new pdg.Point(0, 0), 4, 4, new pdg.Attributes().fillColor(color));
    return drawing;
}

const spark = new pdg.Particle().setDrawing(disc('#ffbb55'))
    .setSize(5, 5).setLifetime(2).fadeTo(0, 2)
    .setTrail({lifetime:.3,width:3,endWidth:0,color:'#ffbb55',minDistance:1,maxPoints:24});
spark.setupPhysicsBody(1, 1);
layer.createParticleEmitter().setParticleTemplate(spark)
    .setLocation(220, 500).setRotation(-Math.PI / 2)
    .setParticleSpeed(150, 230).setSpread(.8).setEmissionRate(90)
    .setSeed(42).startEmitting();

const smoke = new pdg.Particle().setDrawing(disc('#648ed9'))
    .setSize(9, 9).setOpacity(.7).setLifetime(1.2)
    .grow(3, 1.2).fadeTo(0, 1.2);
const rocket = new pdg.Particle().setDrawing(disc('#bdefff'))
    .setSize(14, 6).setLifetime(2.4)
    .setTrail({lifetime:.8,width:9,endWidth:0,color:'#80dfff',minDistance:1,maxPoints:64});
rocket.setupParticleEmitter().setParticleTemplate(smoke)
    .setRotation(Math.PI).setParticleSpeed(4, 12)
    .setEmissionRate(35).setSpread(.3).startEmitting();
layer.createParticleEmitter().setParticleTemplate(rocket)
    .setLocation(630, 520).setRotation(-Math.PI / 2)
    .setParticleSpeed(110, 150).setSpread(.7).setEmissionRate(2)
    .setSeed(7).startEmitting();

layer.onErasePort(function() {
    port.drawRect(port.getDrawingArea(), new pdg.Attributes().fillColor('#111929'));
    return true;
});
layer.onPostDrawLayer(function() {
    const style = new pdg.Attributes().fillColor('white').textSize(20);
    port.drawText('Particles: ' + layer.getParticleCount() + '   Trails: ' + layer.getParticleTrailCount(), new pdg.Point(24, 35), style);
    port.drawText('Physical spark ribbons', new pdg.Point(140, 575), style);
    port.drawText('Rocket ribbons + smoke', new pdg.Point(510, 575), style);
    port.drawText('P: pause / resume   C: clear particles and tails', new pdg.Point(24, 605), new pdg.Attributes().fillColor('#aac0df').textSize(15));
    return true;
});
let paused=false;
pdg.on(pdg.eventType_KeyPress, function(event) {
    if (event.unicode === 112 || event.unicode === 80) { paused=!paused;if(paused)layer.stopAnimations();else layer.startAnimations(); }
    if (event.unicode === 99 || event.unicode === 67) layer.removeAllParticles();
    if (event.unicode === pdg.key_Escape) { pdg.cleanupLayer(layer); pdg.quit(); }
    return false;
});
if (!pdg.visualTestSession && process.argv.indexOf('--wait') < 0) {
    setTimeout(function() { pdg.cleanupLayer(layer); pdg.quit(); }, 6000);
}
pdg.run();
