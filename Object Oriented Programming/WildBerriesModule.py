from PlantModule import Plant
from NullModule import Null


class WildBerries(Plant):
    def __init__(self, world, x, y, stren=99, age=0):
        super(WildBerries, self).__init__(world, x, y, ':', stren, age)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                wb = WildBerries(self.get_world(), new_x, new_y)
                self.get_world().add_organism(wb)
