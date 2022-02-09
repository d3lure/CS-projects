from AnimalModule import Animal
from NullModule import Null


class Sheep(Animal):

    def __init__(self, world, x, y, init=4, stren=4, age=0):
        super().__init__(world, x, y, 'S', init, stren, age)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                s = Sheep(self.get_world(), new_x, new_y)
                self.get_world().add_organism(s)

