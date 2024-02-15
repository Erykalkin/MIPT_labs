import gmsh
import sys

R = 1
r = 0.5
a = 0.4

gmsh.initialize()

lc = 0.1

p0 = gmsh.model.geo.add_point(0, 0, 0, lc)
p0_2 = gmsh.model.geo.add_point(0, 0, r, lc)
p0_4 = gmsh.model.geo.add_point(0, 0, -r, lc)

p1 = gmsh.model.geo.add_point(R, 0, 0, lc)
p2 = gmsh.model.geo.add_point(0, R, 0, lc)
p3 = gmsh.model.geo.add_point(-R, 0, 0, lc)
p4 = gmsh.model.geo.add_point(0, -R, 0, lc)

p1_1 = gmsh.model.geo.add_point(R-r, 0, 0, lc)
p2_1 = gmsh.model.geo.add_point(0, R-r, 0, lc)
p3_1 = gmsh.model.geo.add_point(-R+r, 0, 0, lc)
p4_1 = gmsh.model.geo.add_point(0, r-R, 0, lc)

p1_2 = gmsh.model.geo.add_point(R, 0, r, lc)
p2_2 = gmsh.model.geo.add_point(0, R, r, lc)
p3_2 = gmsh.model.geo.add_point(-R, 0, r, lc)
p4_2 = gmsh.model.geo.add_point(0, -R, r, lc)

p1_3 = gmsh.model.geo.add_point(R+r, 0, 0, lc)
p2_3 = gmsh.model.geo.add_point(0, R+r, 0, lc)
p3_3 = gmsh.model.geo.add_point(-R-r, 0, 0, lc)
p4_3 = gmsh.model.geo.add_point(0, -r-R, 0, lc)

p1_4 = gmsh.model.geo.add_point(R, 0, -r, lc)
p2_4 = gmsh.model.geo.add_point(0, R, -r, lc)
p3_4 = gmsh.model.geo.add_point(-R, 0, -r, lc)
p4_4 = gmsh.model.geo.add_point(0, -R, -r, lc)

s0 = [p1, p2, p3, p4]
s1 = [p1_1, p2_1, p3_1, p4_1]
s2 = [p1_2, p2_2, p3_2, p4_2]
s3 = [p1_3, p2_3, p3_3, p4_3]
s4 = [p1_4, p2_4, p3_4, p4_4]

c1 = [p1_1, p1_2, p1_3, p1_4]
c2 = [p2_1, p2_2, p2_3, p2_4]
c3 = [p3_1, p3_2, p3_3, p3_4]
c4 = [p4_1, p4_2, p4_3, p4_4]

for i in range(4):
    gmsh.model.geo.addCircleArc(s1[i], p0, s1[(i+1)%4], i+1)
    gmsh.model.geo.addCircleArc(s2[i], p0_2, s2[(i+1)%4], i+5)
    gmsh.model.geo.addCircleArc(s3[i], p0, s3[(i+1)%4], i+9)
    gmsh.model.geo.addCircleArc(s4[i], p0_4, s4[(i+1)%4], i+13)
    
    gmsh.model.geo.addCircleArc(c1[i], p1, c1[(i+1)%4], i+17)
    gmsh.model.geo.addCircleArc(c2[i], p2, c2[(i+1)%4], i+21)
    gmsh.model.geo.addCircleArc(c3[i], p3, c3[(i+1)%4], i+25)
    gmsh.model.geo.addCircleArc(c4[i], p4, c4[(i+1)%4], i+29)

gmsh.model.geo.addCurveLoop([1, 21, -5, -17], 1)
gmsh.model.geo.addSurfaceFilling([1], 1)
gmsh.model.geo.addCurveLoop([18, 9, -22, -5], 2)
gmsh.model.geo.addSurfaceFilling([2], 2)
gmsh.model.geo.addCurveLoop([20, 1, -24, -13], 3)
gmsh.model.geo.addSurfaceFilling([3], 3)
gmsh.model.geo.addCurveLoop([19, 13, -23, -9], 4)
gmsh.model.geo.addSurfaceFilling([4], 4)
gmsh.model.geo.addCurveLoop([14, 28, -2, -24], 5)
gmsh.model.geo.addSurfaceFilling([5], 5)
gmsh.model.geo.addCurveLoop([2, 25, -6, -21], 6)
gmsh.model.geo.addSurfaceFilling([6], 6)
gmsh.model.geo.addCurveLoop([23, 14, -27, -10], 7)
gmsh.model.geo.addSurfaceFilling([7], 7)
gmsh.model.geo.addCurveLoop([22, 10, -26, -6], 8)
gmsh.model.geo.addSurfaceFilling([8], 8)
gmsh.model.geo.addCurveLoop([15, 32, -3, -28], 9)
gmsh.model.geo.addSurfaceFilling([9], 9)
gmsh.model.geo.addCurveLoop([26, 11, -30, -7], 10)
gmsh.model.geo.addSurfaceFilling([10], 10)
gmsh.model.geo.addCurveLoop([27, 15, -31, -11], 11)
gmsh.model.geo.addSurfaceFilling([11], 11)
gmsh.model.geo.addCurveLoop([3, 29, -7, -25], 12)
gmsh.model.geo.addSurfaceFilling([12], 12)
gmsh.model.geo.addCurveLoop([16, 20, -4, -32], 13)
gmsh.model.geo.addSurfaceFilling([13], 13)
gmsh.model.geo.addCurveLoop([4, 17, -8, -29], 14)
gmsh.model.geo.addSurfaceFilling([14], 14)
gmsh.model.geo.addCurveLoop([8, 18, -12, -30], 15)
gmsh.model.geo.addSurfaceFilling([15], 15)
gmsh.model.geo.addCurveLoop([31, 16, -19, -12], 16)
gmsh.model.geo.addSurfaceFilling([16], 16)



p0_2_ = gmsh.model.geo.add_point(0, 0, a, lc)
p0_4_ = gmsh.model.geo.add_point(0, 0, -a, lc)

p1_1_ = gmsh.model.geo.add_point(R-a, 0, 0, lc)
p2_1_ = gmsh.model.geo.add_point(0, R-a, 0, lc)
p3_1_ = gmsh.model.geo.add_point(-R+a, 0, 0, lc)
p4_1_ = gmsh.model.geo.add_point(0, a-R, 0, lc)

p1_2_ = gmsh.model.geo.add_point(R, 0, a, lc)
p2_2_ = gmsh.model.geo.add_point(0, R, a, lc)
p3_2_ = gmsh.model.geo.add_point(-R, 0, a, lc)
p4_2_ = gmsh.model.geo.add_point(0, -R, a, lc)

p1_3_ = gmsh.model.geo.add_point(R+a, 0, 0, lc)
p2_3_ = gmsh.model.geo.add_point(0, R+a, 0, lc)
p3_3_ = gmsh.model.geo.add_point(-R-a, 0, 0, lc)
p4_3_ = gmsh.model.geo.add_point(0, -a-R, 0, lc)

p1_4_ = gmsh.model.geo.add_point(R, 0, -a, lc)
p2_4_ = gmsh.model.geo.add_point(0, R, -a, lc)
p3_4_ = gmsh.model.geo.add_point(-R, 0, -a, lc)
p4_4_ = gmsh.model.geo.add_point(0, -R, -a, lc)

s0 = [p1, p2, p3, p4]
s1 = [p1_1_, p2_1_, p3_1_, p4_1_]
s2 = [p1_2_, p2_2_, p3_2_, p4_2_]
s3 = [p1_3_, p2_3_, p3_3_, p4_3_]
s4 = [p1_4_, p2_4_, p3_4_, p4_4_]

c1 = [p1_1_, p1_2_, p1_3_, p1_4_]
c2 = [p2_1_, p2_2_, p2_3_, p2_4_]
c3 = [p3_1_, p3_2_, p3_3_, p3_4_]
c4 = [p4_1_, p4_2_, p4_3_, p4_4_]

for i in range(4):
    gmsh.model.geo.addCircleArc(s1[i], p0, s1[(i+1)%4], i+33)
    gmsh.model.geo.addCircleArc(s2[i], p0_2_, s2[(i+1)%4], i+37)
    gmsh.model.geo.addCircleArc(s3[i], p0, s3[(i+1)%4], i+41)
    gmsh.model.geo.addCircleArc(s4[i], p0_4_, s4[(i+1)%4], i+45)
    
    gmsh.model.geo.addCircleArc(c1[i], p1, c1[(i+1)%4], i+49)
    gmsh.model.geo.addCircleArc(c2[i], p2, c2[(i+1)%4], i+53)
    gmsh.model.geo.addCircleArc(c3[i], p3, c3[(i+1)%4], i+57)
    gmsh.model.geo.addCircleArc(c4[i], p4, c4[(i+1)%4], i+61)


gmsh.model.geo.addCurveLoop([52, 33, -56, -45], 17)
gmsh.model.geo.addSurfaceFilling([17], 17)
gmsh.model.geo.addCurveLoop([56, 34, -60, -46], 18)
gmsh.model.geo.addSurfaceFilling([18], 18)
gmsh.model.geo.addCurveLoop([60, 35, -64, -47], 19)
gmsh.model.geo.addSurfaceFilling([19], 19)
gmsh.model.geo.addCurveLoop([64, 36, -52, -48], 20)
gmsh.model.geo.addSurfaceFilling([20], 20)

gmsh.model.geo.addCurveLoop([49, 37, -53, -33], 21)
gmsh.model.geo.addSurfaceFilling([21], 21)
gmsh.model.geo.addCurveLoop([53, 38, -57, -34], 22)
gmsh.model.geo.addSurfaceFilling([22], 22)
gmsh.model.geo.addCurveLoop([57, 39, -61, -35], 23)
gmsh.model.geo.addSurfaceFilling([23], 23)
gmsh.model.geo.addCurveLoop([61, 40, -49, -36], 24)
gmsh.model.geo.addSurfaceFilling([24], 24)

gmsh.model.geo.addCurveLoop([50, 41, -54, -37], 25)
gmsh.model.geo.addSurfaceFilling([25], 25)
gmsh.model.geo.addCurveLoop([54, 42, -58, -38], 26)
gmsh.model.geo.addSurfaceFilling([26], 26)
gmsh.model.geo.addCurveLoop([58, 43, -62, -39], 27)
gmsh.model.geo.addSurfaceFilling([27], 27)
gmsh.model.geo.addCurveLoop([62, 44, -50, -40], 28)
gmsh.model.geo.addSurfaceFilling([28], 28)

gmsh.model.geo.addCurveLoop([51, 45, -55, -41], 29)
gmsh.model.geo.addSurfaceFilling([29], 29)
gmsh.model.geo.addCurveLoop([55, 46, -59, -42], 30)
gmsh.model.geo.addSurfaceFilling([30], 30)
gmsh.model.geo.addCurveLoop([59, 47, -63, -43], 31)
gmsh.model.geo.addSurfaceFilling([31], 31)
gmsh.model.geo.addCurveLoop([63, 48, -51, -44], 32)
gmsh.model.geo.addSurfaceFilling([32], 32)

l = gmsh.model.geo.addSurfaceLoop([i + 1 for i in range(32)])
gmsh.model.geo.addVolume([l])


gmsh.model.geo.synchronize()

gmsh.model.mesh.generate(3)

gmsh.write("t2.msh")
gmsh.write("t2.geo_unrolled")

if '-nopopup' not in sys.argv:
    gmsh.fltk.run()

gmsh.finalize()
