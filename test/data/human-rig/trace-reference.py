#!/usr/bin/env python3
"""Extract the stationary figure and split it into overlapping articulated pieces.

Run from any directory. macOS uses its built-in sips decoder; other platforms
need Pillow only when retracing. Ordinary SCML/PNG generation requires Node alone.
"""
import json, math, hashlib, shutil, struct, subprocess, tempfile
from pathlib import Path
from collections import defaultdict

root = Path(__file__).resolve().parent
source = root / 'reference.jpg'

def decode_rgb():
    if shutil.which('sips'):
        with tempfile.TemporaryDirectory(prefix='pdg-reference-') as directory:
            bitmap = Path(directory) / 'reference.bmp'
            subprocess.run(['sips', '-s', 'format', 'bmp', str(source), '--out', str(bitmap)],
                           check=True, stdout=subprocess.DEVNULL)
            data = bitmap.read_bytes()
        offset = struct.unpack_from('<I', data, 10)[0]
        _, width, height, planes, depth, compression = struct.unpack_from('<IiiHHI', data, 14)
        if planes != 1 or depth != 24 or compression != 0:
            raise ValueError('Expected an uncompressed RGB BMP from sips')
        stride = (width * 3 + 3) & ~3
        rgb = bytearray(width * abs(height) * 3)
        for y in range(abs(height)):
            row = y if height < 0 else height - y - 1
            for x in range(width):
                src = offset + row * stride + x * 3
                dst = (y * width + x) * 3
                rgb[dst:dst+3] = data[src:src+3][::-1]
        return width, abs(height), rgb
    try:
        from PIL import Image
    except ImportError as error:
        raise SystemExit('Retracing requires macOS sips or Python Pillow.') from error
    with Image.open(source) as image:
        rgb = image.convert('RGB')
        return image.width, image.height, rgb.tobytes()

width, height, raw = decode_rgb()
if (width, height) != (1408, 768):
    raise ValueError('Landmarks expect the original 1408 x 768 reference image')
mask=set()
for y in range(154,678):
 for x in range(1200,1355):
  pixel=raw[(y*width+x)*3:(y*width+x)*3+3]
  if max(pixel)<(25 if y<660 else 12):
   if y>=660 and 1273<=x<=1285:continue
   mask.add((x,y))
# Keep the character and attached hair wisps, excluding JPEG/background speckles.
component={(1278,270)};todo=list(component)
while todo:
 x,y=todo.pop()
 for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
  if p in mask and p not in component:component.add(p);todo.append(p)
mask=component
pixels_per_cm=(678-min(y for x,y in mask))/170
wrist_inset_cm=3
print('Mask',len(mask),'bounds',min(x for x,y in mask),min(y for x,y in mask),max(x for x,y in mask),max(y for x,y in mask))
parents={'root':None,'torso':'root','neck':'torso','head':'neck',
 'right_upper_arm':'torso','right_forearm':'right_upper_arm','right_hand':'right_forearm',
 'left_upper_arm':'torso','left_forearm':'left_upper_arm','left_hand':'left_forearm',
 'right_thigh':'root','right_shin':'right_thigh','right_foot':'right_shin',
 'left_thigh':'root','left_shin':'left_thigh','left_foot':'left_shin'}
joints={'root':[[1278,418],[1278,356]],'torso':[[1278,356],[1278,259]],
 'neck':[[1278,259],[1278,241]],'head':[[1278,241],[1278,166]],
 'right_upper_arm':[[1237,282],[1226,355]],'right_forearm':[[1226,355],[1216,428]],'right_hand':[[1216,428],[1218,461]],
 'left_upper_arm':[[1320,282],[1330,355]],'left_forearm':[[1330,355],[1341,429]],'left_hand':[[1341,429],[1338,462]],
 'right_thigh':[[1252,415],[1255,536]],'right_shin':[[1255,536],[1259,644]],'right_foot':[[1259,644],[1238,644]],
 'left_thigh':[[1305,415],[1303,536]],'left_shin':[[1303,536],[1299,644]],'left_foot':[[1299,644],[1320,644]]}
# Place each wrist 3 cm farther up the forearm. Repartition the traced art at
# the new joint so the hand owns the short section below it and bends cleanly.
for side in ['right','left']:
 forearm=joints[side+'_forearm'];hand=joints[side+'_hand']
 length=math.dist(*forearm)
 wrist=[forearm[1][i]+(forearm[0][i]-forearm[1][i])*wrist_inset_cm*pixels_per_cm/length for i in [0,1]]
 forearm[1]=wrist;hand[0]=wrist
z={'right_upper_arm':0,'right_forearm':1,'right_hand':2,'right_thigh':3,'right_shin':4,'right_foot':5,
 'left_thigh':6,'left_shin':7,'root':8,'torso':9,'neck':10,'head':11,'left_upper_arm':12,'left_forearm':13,'left_hand':14,'left_foot':15}
def label(x,y):
 if y<245:return 'head'
 if y<260:return 'neck'
 cuts=[(260,1246),(290,1245),(320,1244),(340,1241),(356,1240),(390,1230),(410,1225),(430,1226),(480,1227)]
 cut=cuts[-1][1]
 for (a,u),(b,v) in zip(cuts,cuts[1:]):
  if a<=y<b:cut=u+(v-u)*(y-a)/(b-a);break
 if x<cut:return 'right_upper_arm' if y<355 else 'right_forearm' if y<joints['right_hand'][0][1] else 'right_hand'
 if x>2557-cut:return 'left_upper_arm' if y<355 else 'left_forearm' if y<joints['left_hand'][0][1] else 'left_hand'
 if y<356:return 'torso'
 if y<418:return 'root'
 side='right' if x<1278 else 'left'
 return side+('_thigh' if y<536 else '_shin' if y<643 else '_foot')
regions={name:set() for name in parents}
for x,y in mask:regions[label(x,y)].add((x,y))

def inside(p,poly):
 yes=False;x,y=p
 for a,b in zip(poly,poly[1:]+poly[:1]):
  if (a[1]>y)!=(b[1]>y) and x<(b[0]-a[0])*(y-a[1])/(b[1]-a[1])+a[0]:yes=not yes
 return yes

def ellipse(cx,cy,rx,ry):
 return {p for p in mask if ((p[0]+.5-cx)/rx)**2+((p[1]+.5-cy)/ry)**2<=1}

def shoulder_edge(y):
 # The raised-arm reference shows a continuous flare from chest to shoulder,
 # not a circular bulge ending at the armpit. This internal shirt edge follows
 # that taper and is covered by the upper arm in the resting pose.
 lo,hi=0.,1.
 for _ in range(20):
  t=(lo+hi)/2;u=1-t
  by=u**3*270+3*u*u*t*287+3*u*t*t*302+t**3*325
  if by<y:lo=t
  else:hi=t
 t=(lo+hi)/2;u=1-t
 return u**3*1330+3*u*u*t*1324+3*u*t*t*1313+t**3*1312

# Articulated cutouts need hidden volume, not straight slices of the resting
# silhouette. Round both sides of each joint, while keeping new pixels inside
# the original figure so the assembled reference outline stays unchanged.
for side in ['right','left']:
 arm=side+'_upper_arm'; forearm=side+'_forearm'; thigh=side+'_thigh'
 sx,sy=joints[arm][0]
 shoulder=ellipse(sx,sy,19,19)
 # Remove the square proximal corner that swung out with the sleeve.
 regions[arm]={p for p in regions[arm] if p[1]>=sy}|shoulder
 # The short sleeve, including its normally hidden lower hem, belongs to
 # the upper arm. Extend it inward under the torso so the cuff is revealed
 # as the arm rises. Coordinates are along the arm and toward the torso.
 tx,ty=joints[arm][1];length=math.hypot(tx-sx,ty-sy)
 ux,uy=(tx-sx)/length,(ty-sy)/length
 inward=1 if side=='left' else -1
 sleeve=[(sx+u*ux-v*uy*inward,sy+u*uy+v*ux*inward) for u,v in
         [(-12,-10),(0,-19),(13,-17),(16,-13),(18,15),(10,18),(0,19),(-12,12)]]
 regions[arm]|={p for p in mask if inside((p[0]+.5,p[1]+.5),sleeve)}
 # A broad, rounded pelvis extends down to the crotch, overlapping the thighs.
 hx,hy=joints[thigh][0]
 regions[thigh]|=ellipse(hx,hy,29,29)

regions['torso']={p for p in regions['torso'] if p[1]>=325}
regions['torso']|={p for p in mask if 259<=p[1]<270}
for y in range(270,325):
 edge=shoulder_edge(y+.5)
 regions['torso']|={p for p in mask if p[1]==y and 2557-edge<=p[0]+.5<=edge}

regions['root']={p for p in regions['root'] if p[1]<398}|ellipse(1278,398,51,30.5)

for side in ['right','left']:
 for parent,child,radius in [('upper_arm','forearm',10.5),('forearm','hand',5.5),
                             ('thigh','shin',14),('shin','foot',8)]:
  cx,cy=joints[side+'_'+child][0]
  cap=ellipse(cx,cy,radius,radius)
  regions[side+'_'+parent]|=cap
  regions[side+'_'+child]|=cap

# Round the neck at both ends and the waist inside the shirt as well.
for parent,child,cx,cy,rx,ry in [('torso','neck',1278,259,11,11),
                               ('neck','head',1278,241,11,11),
                               ('root','torso',1278,356,32,18)]:
 cap=ellipse(cx,cy,rx,ry)
 regions[parent]|=cap
 regions[child]|=cap

# Preserve visible sleeve/hip outline pixels excluded by the rounded internal
# cuts. They belong to the adjoining piece, rather than becoming cutout gaps.
covered=set().union(*regions.values())
for x,y in mask-covered:
 owner=label(x,y)
 if owner.endswith('upper_arm') and y<282:owner='torso'
 if owner=='root' and y>=398:owner='right_thigh' if x<1278 else 'left_thigh'
 regions[owner].add((x,y))

# A narrow lap along internal seams accommodates the small counter-rotation of
# torso and limbs. The rounded caps provide the larger overlap at bent joints.
for region in regions.values():
 front=set(region)
 for _ in range(2):
  front={(x+dx,y+dy) for x,y in front for dx,dy in [(-1,0),(1,0),(0,-1),(0,1)]
         if (x+dx,y+dy) in mask}-region
  region|=front

def area(poly):return sum(x*poly[(i+1)%len(poly)][1]-y*poly[(i+1)%len(poly)][0] for i,(x,y) in enumerate(poly))/2

def boundaries(region):
 edges=set()
 for x,y in region:
  for n,a,b in [((x,y-1),(x,y),(x+1,y)),((x+1,y),(x+1,y),(x+1,y+1)),((x,y+1),(x+1,y+1),(x,y+1)),((x-1,y),(x,y+1),(x,y))]:
   if n not in region:edges.add((a,b))
 out=defaultdict(list)
 for a,b in edges:out[a].append(b)
 paths=[]
 while edges:
  a,b=min(edges); start=a;poly=[a]
  while True:
   edges.remove((a,b));poly.append(b)
   if b==start:break
   candidates=[p for p in out[b] if (b,p) in edges]
   ux,uy=b[0]-a[0],b[1]-a[1]
   def turn(p):
    vx,vy=p[0]-b[0],p[1]-b[1]
    return {1:0,0:1,-1:2}[ux*vy-uy*vx]
   a,b=b,min(candidates,key=turn)
  paths.append(poly[:-1])
 return paths

def distance(p,a,b):
 dx,dy=b[0]-a[0],b[1]-a[1]
 t=max(0,min(1,((p[0]-a[0])*dx+(p[1]-a[1])*dy)/(dx*dx+dy*dy))) if dx or dy else 0
 return math.hypot(p[0]-a[0]-t*dx,p[1]-a[1]-t*dy)
def simplify(poly,tol=.45):
 def rdp(points):
  if len(points)<3:return points
  ds=[distance(p,points[0],points[-1]) for p in points[1:-1]]
  i=max(range(len(ds)),key=ds.__getitem__)+1
  if ds[i-1]<=tol:return [points[0],points[-1]]
  return rdp(points[:i+1])[:-1]+rdp(points[i:])
 # Cut the closed contour at two separated points before RDP.
 mid=max(range(len(poly)),key=lambda i:math.dist(poly[0],poly[i]))
 return rdp(poly[:mid+1])[:-1]+rdp(poly[mid:]+poly[:1])[:-1]

def bridge(outer,hole):
 # The shortest bridge stays inside this small, simply nested silhouette.
 _,oi,hi=min((math.dist(a,b),i,j) for i,a in enumerate(outer) for j,b in enumerate(hole))
 return outer[:oi+1]+hole[hi:]+hole[:hi+1]+[outer[oi]]+outer[oi+1:]
def contours(region):
 paths=[simplify(p) for p in boundaries(region)]
 outers=[p for p in paths if area(p)>0];holes=[p for p in paths if area(p)<0]
 for hole in holes:
  for i,outer in enumerate(outers):
   if inside(hole[0],outer):outers[i]=bridge(outer,hole);break
 return outers

def cubic(points):
 # Sample smooth artwork in source-pixel units. Keeping vertices at least
 # .45 pixels apart also respects Polygon.addPoint's existing millimeter-scale
 # filtering when human.js converts these contours into Drawing coordinates.
 count=max(4,math.ceil(sum(math.dist(a,b) for a,b in zip(points,points[1:]))/.8))
 result=[]
 for i in range(count+1):
  t=i/count;u=1-t
  p=tuple(u**3*points[0][a]+3*u*u*t*points[1][a]+3*u*t*t*points[2][a]+t**3*points[3][a] for a in [0,1])
  if not result or math.dist(result[-1],p)>=.45:result.append(p)
 if math.dist(result[-1],points[-1])<.45:result[-1]=points[-1]
 else:result.append(points[-1])
 return result

def refine_arm(name,outline):
 # The marked corrections concern the bare inner upper arm and both elbow
 # ends. Preserve the sleeve, outer upper arm, and forearm/wrist outline.
 # Work along each bone, with transverse +y pointing inward on either side.
 joint,tip=joints[name];length=math.dist(joint,tip)
 ux,uy=(tip[0]-joint[0])/length,(tip[1]-joint[1])/length
 inward=1 if name.startswith('left') else -1
 poly=[((x-joint[0])*ux+(y-joint[1])*uy,
        (-(x-joint[0])*uy+(y-joint[1])*ux)*inward) for x,y in outline]
 upper=name.endswith('upper_arm')

 def edge(x,inner):
  hits=[]
  for i,a in enumerate(poly):
   b=poly[(i+1)%len(poly)]
   if (a[0]>x)!=(b[0]>x):
    t=(x-a[0])/(b[0]-a[0]);slope=(b[1]-a[1])/(b[0]-a[0])
    hits.append((i,t,(x,a[1]+t*(b[1]-a[1])),slope))
  return (max if inner else min)(hits,key=lambda hit:hit[2][1])

 outer=edge(length-7 if upper else 6,False)
 inner=edge(32 if upper else 6,True)
 a,b=outer[2],inner[2]
 segments=[]
 if upper:
  # Ease the untouched outer edge into the cap. The inner arm flows from
  # the marked biceps edge into the same cap without the old shelf/step.
  low=a[1]+outer[3]*7*.5
  high=9.5
  d=(length,low);e=(length,high)
  segments.append([a,(a[0]+2.5,a[1]+2.5*outer[3]),(length-2.5,low),d])
 else:
  # The forearm's proximal end is a cap, rather than a circle superimposed
  # on the old horizontal cut. Blend it into both retained forearm edges.
  low=a[1]-outer[3]*3;high=b[1]-inner[3]*3
  d=(0,low);e=(0,high)
  segments.append([a,(a[0]-2,a[1]-2*outer[3]),(2,low),d])
 center=(low+high)/2;radius=(high-low)/2
 direction=1 if upper else -1
 tip_point=(d[0]+direction*10,center)
 k=.5522847498307936
 segments.extend([[d,(d[0]+direction*10*k,low),(tip_point[0],center-radius*k),tip_point],
                  [tip_point,(tip_point[0],center+radius*k),(e[0]+direction*10*k,high),e]])
 if upper:
  segments.append([e,(length-12,high),(b[0]+10,b[1]+10*inner[3]),b])
 else:
  segments.append([e,(2,high),(b[0]-2,b[1]-2*inner[3]),b])
 replacement=[]
 for segment in segments:replacement.extend(cubic(segment)[:-1])
 replacement.append(b)

 # Replace only the boundary arc passing around the elbow. The other arc
 # remains the traced outline, including the shirt sleeve and wrist detail.
 ring=[];indices={}
 for i,p in enumerate(poly):
  ring.append(p)
  for label,hit in sorted([('outer',outer),('inner',inner)],key=lambda item:item[1][1]):
   if hit[0]==i:indices[label]=len(ring);ring.append(hit[2])
 def arc(start,end):
  return [ring[i%len(ring)] for i in range(start,end+1 if end>=start else end+len(ring)+1)]
 ab=arc(indices['outer'],indices['inner']);ba=arc(indices['inner'],indices['outer'])
 ab_is_cap=max(p[0] for p in ab)>length+1 if upper else min(p[0] for p in ab)<-1
 result=replacement[:-1]+ba[:-1] if ab_is_cap else list(reversed(replacement))[:-1]+ab[:-1]
 clean=[]
 for p in result:
  if not clean or math.dist(clean[-1],p)>=.45:clean.append(p)
 if math.dist(clean[-1],clean[0])<.45:clean.pop()
 return [(joint[0]+x*ux-y*uy*inward,joint[1]+x*uy+y*ux*inward) for x,y in clean]

parts=[]
for name in parents:
 outers=contours(regions[name])
 if name.endswith(('upper_arm','forearm')):
  outers=[refine_arm(name,outline) for outline in outers]
 parts.append({'name':name,'parent':parents[name],'joint':joints[name][0],'tip':joints[name][1],'z':z[name], 'contours':outers})
 print(name,len(regions[name]),[len(p) for p in outers])

# Open greeting hand from the first waving figure in the same supplied image.
# Preserve the palm/fingers as one cutout; the wrist is its attachment point.
open_tip=[234,215];open_joint=[231,263]
length=math.dist(open_joint,open_tip)
open_joint=[open_joint[i]+(open_joint[i]-open_tip[i])*wrist_inset_cm*pixels_per_cm/length for i in [0,1]]
open_hand={(x,y) for y in range(205,math.ceil(open_joint[1]+7)) for x in range(208,253)
           if (y<open_joint[1] or (x+.5-open_joint[0])**2+(y+.5-open_joint[1])**2<=6**2)
           and max(raw[(y*width+x)*3:(y*width+x)*3+3])<25}
component={(232,248)};todo=list(component)
while todo:
 x,y=todo.pop()
 for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
  if p in open_hand and p not in component:component.add(p);todo.append(p)
open_hand=component
variants=[{'name':'left_hand_open','bone':'left_hand','joint':open_joint,
           'tip':open_tip,'contours':contours(open_hand)}]
runs=[]
for y in range(154,678):
 xs=sorted(x for x,yy in mask if yy==y)
 if not xs:continue
 row=[y];a=prev=xs[0]
 for x in xs[1:]:
  if x>prev+1:row.extend([a,prev+1]);a=x
  prev=x
 row.extend([a,prev+1]);runs.append(row)
trace={'source':'reference.jpg','sourceSha256':hashlib.sha256(source.read_bytes()).hexdigest(),'sourceSize':[1408,768], 'origin':[1278,678],'heightCm':170,
 'pixelsPerCm':pixels_per_cm,
 'extraction':{'maxChannelExclusive':25,'feetMaxChannelExclusive':12,'feetStartY':660,'roundedJoints':True,'simplifyTolerancePixels':.45,'wristInsetCm':wrist_inset_cm},
 'parts':parts,'variants':variants,'maskRuns':runs}
(root / 'reference-trace.js').write_text('// Generated by trace-reference.py from reference.jpg: rightmost resting figure and first waving hand.\n// Image-pixel contours, rounded joint overlaps, anatomical landmarks, and the comparison mask.\n// Preserve the source outline: sleeve edges, hems, shoe soles, fingers and hair.\nmodule.exports = '+json.dumps(trace,separators=(',',':'))+';\n')
