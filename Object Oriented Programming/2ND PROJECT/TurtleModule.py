from AnimalModule import Animal
from NullModule import Null
import random


class Turtle(Animal):

    def __init__(self, world, x, y, init=1, stren=2, age=0):
        super(Turtle, self).__init__(world, x, y, 'T', 1, 2, 0)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                t = Turtle(self.get_world(), new_x, new_y)
                self.get_world().add_organism(t)

    def action(self):
        if random.randrange(100) > 75:
            super().action()

    def collision(self, collider):
        if type(self) != type(collider):
            if collider.get_strength() < 5:
                log = "T defended himself from "
                log += collider.draw()
                self.get_world().set_feed(log)
            else:
                super().collision(collider)
        else:
            self.reproduce()
