from Global import Global
from Entity import Entity
from Game import Game
from Extractor import Extractor

import re

class Parser:
	
	def __init__(self, pathInput):
		self.pathInput = pathInput
		self.globalBloc = None
		self.game = None
		self.entities = []

	def analyse(self):
		fichier = open(self.pathInput)
		titreBloc = ""
		bufferBloc = ""
		for ligne in iter(fichier):
			if re.match(r'^\s*$', ligne):
				continue
			nbTabs = len(ligne) - len(ligne.lstrip('\t'))
			if nbTabs == 0:
				self.decodeBloc(titreBloc, bufferBloc)
				titreBloc = ligne
				bufferBloc = ""
			else:
				bufferBloc += ligne.lstrip('\t')
		self.decodeBloc(titreBloc, bufferBloc)
		fichier.close()

	def decodeBloc(self, titre, bloc):
		globalName = Extractor.extractBloc('Global', titre)
		entityName = Extractor.extractBloc('Entity', titre)
		gameName = Extractor.extractBloc('Game', titre)
		if globalName:
			nouveau = Global()
			nouveau.decode(bloc)
			self.globalBloc = nouveau
		elif entityName:
			nouveau = Entity(entityName)
			nouveau.decode(bloc)
			self.entities.append(nouveau)
		elif gameName:
			nouveau = Game()
			nouveau.decode(bloc)
			self.game = nouveau
