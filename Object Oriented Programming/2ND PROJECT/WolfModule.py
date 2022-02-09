from AnimalModule import Animal
from NullModule import Null


class Wolf(Animal):

    def __init__(self, world, x, y, init=5, stren=9, age=0):
        super(Wolf, self).__init__(world, x, y, 'W', 5, 9, 0)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                w = Wolf(self.get_world(), new_x, new_y)
                self.get_world().add_organism(w)
