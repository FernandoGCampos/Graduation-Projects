import glm

pos: glm.vec4 = glm.vec4(1.0)
pos.x = 100
pos.y = -100

proj: glm.mat4 = glm.ortho(-50, 150, -100, 100, 1, -1)
print(proj)