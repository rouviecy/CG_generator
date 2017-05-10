from Indentable import Indentable

class Makefile(Indentable):

	def __init__(self, workspace):
		self.workspace = workspace

	def write(self, entities):
		readonlyMakefile = open(self.workspace + "readonly/CMakeLists.txt", 'w')
		readonlyMakefile.write(self.genReadonlyMakefile(entities))

	def genReadonlyMakefile(self, entities):
		text = "cmake_minimum_required(VERSION 2.8)\n"
		text += "project(cg_generator)\n\n"
		text += "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11\")\n\n"
		text += "add_library(CG_GENERATOR\n"
		text += self.indent(1) + "../readonly/common_readonly.h\n"
		text += self.indent(1) + "../readonly/Game_readonly.h\n"
		text += self.indent(1) + "../readonly/Game_readonly.cpp\n"
		text += self.indent(1) + "../readonly/Entity_readonly.h\n"
		text += self.indent(1) + "../readonly/Entity_readonly.cpp\n"
		for entity in entities:
			text += self.indent(1) + "../readonly/entities/" + entity.nameRE + ".h\n"
			text += self.indent(1) + "../readonly/entities/" + entity.nameRE + ".cpp\n"
		text += self.indent(1) + "../custom/common.h\n"
		text += self.indent(1) + "../custom/Game.h\n"
		text += self.indent(1) + "../custom/Game.cpp\n"
		text += self.indent(1) + "../custom/Entity.h\n"
		text += self.indent(1) + "../custom/Entity.cpp\n"
		for entity in entities:
			text += self.indent(1) + "../custom/entities/" + entity.name + ".h\n"
			text += self.indent(1) + "../custom/entities/" + entity.name + ".cpp\n"
		text += ")\n\n"
		text += "add_executable(cg ../readonly/main_readonly.cpp)\n"
		text += "target_link_libraries(cg CG_GENERATOR)"
		text += "\n\n"
		text += "add_executable(cgcode ../readonly/mainMono_readonly.cpp)\n"
		text += "set_target_properties(cgcode PROPERTIES COMPILE_FLAGS \"-E -P -DEXPLICITE_EXCLUDE\")"
		return text
