from PlantModule import Plant
from NullModule import Null
import random


class Dandelion(Plant):

    def __init__(self, world, x, y, stren=0, age=0):
        super(Dandelion, self).__init__(world, x, y, '*', stren, age)

    def action(self):
        for i in range(3):
            if random.randrange(100) < 20:
                self.reproduce()
                break

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                d = Dandelion(self.get_world(), new_x, new_y)
                self.get_world().add_organism(d)
