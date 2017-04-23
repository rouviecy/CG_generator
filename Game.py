from Extractor import Extractor

class Game:
	
	def __init__(self):
		self.argumentsGame = []
		self.argumentsTurn = []
		self.variables = []
		self.argumentNbEntities = None
		self.nbEntityArgs = 0

	def decode(self, bloc):
		self.argumentsGame = Extractor.extractList('argsGame', bloc)
		self.argumentsTurn = Extractor.extractList('argsTurn', bloc)
		self.variables = Extractor.extractList('vars', bloc)
		self.argumentNbEntities = Extractor.extractParam('argumentNbEntities', bloc)
		self.nbEntityArgs = int(Extractor.extractParam('nbEntityArgs', bloc))
