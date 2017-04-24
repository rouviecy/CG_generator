from Indentable import Indentable

class Makefile(Indentable):

	def __init__(self):
		pass

	def write(self, entities):
		readonlyMakefile = open("./CPP/readonly/CMakeLists_readonly.txt", 'w')
		readonlyMakefile.write(self.genReadonlyMakefile(entities))
		templateMakefile = open("./CPP/template/CMakeLists.txt", 'w')
		templateMakefile.write(self.genTemplateMakefile())

	def genReadonlyMakefile(self, entities):
		text = "cmake_minimum_required(VERSION 2.8)\n"
		text += "project(cg)\n\n"
		text += "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11\")\n\n"
		text += "add_library(CG_GENERATOR\n"
		text += self.indent(1) + "CPP/readonly/common_readonly.h\n"
		text += self.indent(1) + "CPP/readonly/Game_readonly.h\n"
		text += self.indent(1) + "CPP/readonly/Game_readonly.cpp\n"
		text += self.indent(1) + "CPP/readonly/Entity_readonly.h\n"
		text += self.indent(1) + "CPP/readonly/Entity_readonly.cpp\n"
		for entity in entities:
			text += self.indent(1) + "CPP/readonly/entities/" + entity.nameRE + ".h\n"
			text += self.indent(1) + "CPP/readonly/entities/" + entity.nameRE + ".cpp\n"
		text += self.indent(1) + "CPP/custom/common.h\n"
		text += self.indent(1) + "CPP/custom/Game.h\n"
		text += self.indent(1) + "CPP/custom/Game.cpp\n"
		text += self.indent(1) + "CPP/custom/Entity.h\n"
		text += self.indent(1) + "CPP/custom/Entity.cpp\n"
		for entity in entities:
			text += self.indent(1) + "CPP/custom/entities/" + entity.name + ".h\n"
			text += self.indent(1) + "CPP/custom/entities/" + entity.name + ".cpp\n"
		text += ")\n\n"
		text += "add_executable(cg CPP/readonly/main.cpp)\n"
		text += "target_link_libraries(cg CG_GENERATOR)"
		return text

	def genTemplateMakefile(self):
		text = "cmake_minimum_required(VERSION 2.8)\n"
		text += "project(cg)\n\n"
		text += "include(${CMAKE_CURRENT_SOURCE_DIR}/CPP/readonly/CMakeLists_readonly.txt)\n"
		return text
