functionsToInit = """glGetString
glGetIntegerv
glGetError
glClearColor
glClear
glGenBuffers
glBindBuffer
glCreateProgram
glCreateShader
glShaderSource
glCompileShader
glGetShaderiv
glGetShaderInfoLog
glAttachShader
glLinkProgram
glUseProgram
glDeleteShader
glDrawElements
glBufferData
glEnableVertexAttribArray
glVertexAttribPointer
glGenVertexArrays
glBindVertexArray
glDrawArrays""".split("\n")

HEADER = "#pragma once\n"
for f in functionsToInit:
    HEADER += "extern PFN{}PROC {};\n".format(f.upper(), f)

CPP = ""
for f in functionsToInit:
    CPP += "PFN{}PROC {} = nullptr;\n".format(f.upper(), f)

CPP += "\nstatic void initGLean() {\n"
for f in functionsToInit:
    CPP += "\tINIT_FUNC({});\n".format(f)
CPP += "}"

print("HEADER:")
print(HEADER)
print("")
print("CPP:")
print(CPP)

h = open("autogen_header.h", 'w')
h.writelines(HEADER)
cpp = open("autogen_cpp.h", 'w')
cpp.writelines(CPP)
