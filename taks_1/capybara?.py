import gmsh
import sys


gmsh.initialize()

gmsh.merge(R"C:\Users\George.LAPTOP-TLP259VH\Desktop\d20.stl")
n = gmsh.model.getDimension()
s = gmsh.model.getEntities(n)
l = gmsh.model.geo.addSurfaceLoop([s[i][1] for i in range(len(s))])

gmsh.model.geo.addVolume([l])
gmsh.model.geo.synchronize()

gmsh.model.mesh.generate(3)

gmsh.write("t2.msh")
gmsh.write("t2.geo_unrolled")

if '-nopopup' not in sys.argv:
    gmsh.fltk.run()

gmsh.finalize()
