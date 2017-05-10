class Indentable:
	
	def __init__(self):
		pass

	def indent(self, nb):
		indentItem = "    "
		text = ""
		for i in range(nb):
			text += indentItem
		return text
