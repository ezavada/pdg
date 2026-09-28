# C++ MVC application framework

The C++ and JavaScript frameworks share the View animation, theme composition,
clipping and input contracts. Views derive from `AnimatedAttributes<View>` and
have no physics body. Controllers step each registered view once before drawing;
time parameters use seconds and rotation uses radians clockwise.

`getViewArea()` is the unrotated layout rectangle. Location is its center, and
width/height control layout independently of scale. Movement and resizing update
clickable regions and call `viewAreaChanged(previous)`. Overrides call the base
before arranging their own content.

Controls first resolve their `ControlAttributes` state (with Normal fallback),
then apply explicitly assigned or scheduled View appearance channels. Unset
channels preserve the theme; explicitly setting a default value still overrides
it. `getDrawingAttributes(theme, true)` preserves label foreground colors while
applying text/font, fill opacity and blend settings. Custom ControlAttributes draw
routines receive the composed `ControlStateAttributes::drawing` sample; use that
sample to honor overrides. Neither the View nor theme is modified by composition.

```cpp
button.fillColor(pdg::Color(0.2f, 0.4f, 0.8f))
      .changeFillOpacity(0.5f, 0.8)
      .rotateTo(0.12f, 0.8);
```

`View::draw()` clips and transforms all of `drawSelf()`, including text, images
and custom routines. Rotated/reflected/sheared views reuse an offscreen surface;
resizing the viewport reallocates it. The inherited Attributes sample can still
be used for centered unit-coordinate drawing. Inside `drawSelf()`,
`localToGlobal()` produces untransformed Port layout coordinates. Outside drawing,
it maps to the transformed destination. `globalToLocal()` applies the inverse,
so clickable parts match the image. Rectangle conversions return bounds of all
four transformed corners. Zero-scale views cannot be hit.

`ScrollingView` clips to `getViewFrame()` while content is laid out in
`getViewArea()`. `setViewFrame()` resizes its viewport. All drawing intersects the
previous Port clip and restores it, including on exceptions. The viewport itself
is transformed with the view, so rotated clipping follows its actual rectangle.
Port continues to have one clip rectangle, with no public clip stack.

Use `child.setParentView(&parent)` for composites registered with the same
Controller. This is a non-owning visual link: the parent draws children once,
clips them, and supplies inherited visibility and transforms. Controllers still
step each view once and route input to the frontmost descendant. Child layout
rectangles remain in Port coordinates and follow parent movement and resizing.
`setParentView(nullptr)` detaches, cycles are rejected, and destruction unlinks
both directions. ListBox uses this relationship for its scrollbar.

Native controllers retain registered views and release them on removal. View
destruction releases its reusable render surface. Keep the controller/view
lifetime inside the lifetime of its graphics port.

Build `pdg-app-control-gallery` for the native gallery. The usual `test/demo mvc`
entry runs the JavaScript gallery, with the same controls and transform/scrolling
examples; `--web` and `--ios` select the other graphics runtimes. Focused CTest
suites are `pdg-view-animation`, `pdg-app-framework`, and `pdg-app-view-utils`.
