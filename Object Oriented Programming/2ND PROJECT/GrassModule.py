from PlantModule import Plant


class Grass(Plant):

    def __init__(self, world, x, y, stren=0, age=0):
        super(Grass, self).__init__(world, x, y, '"', stren, age)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            empty = self.is_empty(new_x,  new_y)
            if empty is True:
                g = Grass(self.get_world(), new_x, new_y)
                self.get_world().add_organism(g)
