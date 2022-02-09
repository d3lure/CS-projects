from OrganismModule import Organism


class Null(Organism):

    def __init__(self):
        super().__init__(None, None, None, '_')

    def action(self):
        pass

    def collision(self, collider):
        pass

    def print_self(self):
        pass

    def get_sign(self):
        return '_'
