functionsToInit = """glGetString
glGetIntegerv
glGetError
glClearColor
glClear
glCreateBuffers
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
glDeleteShader""".split("\n")

HEADER = ""
for f in functionsToInit:
    HEADER += "extern PFN{}PROC {};\n".format(f.upper(), f)

CPP = ""
for f in functionsToInit:
    CPP += "PFN{}PROC {} = nullptr;\n".format(f.upper(), f)

print("HEADER:")
print(HEADER)
print("")
print("CPP:")
print(CPP)

## # TODO: Save the files automatically
