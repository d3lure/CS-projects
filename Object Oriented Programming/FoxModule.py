from AnimalModule import Animal
from NullModule import Null


class Fox(Animal):
    def __init__(self, world, x, y, init=7, stren=3, age=0):
        super(Fox, self).__init__(world, x, y, 'F', init, stren, age)

    def action(self):
        new_x, new_y = self.new_position()
        empty = self.is_empty(new_x, new_y)

        if empty is True:
            self.set_position(new_x, new_y)
        else:
            if empty.get_strength() > self.get_strength():
                log = "F decided not to fight with "
                log += empty.draw()
                self.get_world().set_feed(log)
            else:
                empty.collision(self)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                f = Fox(self.get_world(), new_x, new_y)
                self.get_world().add_organism(f)