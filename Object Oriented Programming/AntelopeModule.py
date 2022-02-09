from AnimalModule import Animal
from NullModule import Null
import random


class Antelope(Animal):

    def __init__(self, world, x, y, init=4, stren=4, age=0):
        super(Antelope, self).__init__(world, x, y, 'A', init, stren, age)

    def collision(self, collider):
        if type(self) != type(collider):
            if collider.get_strength() >= self.get_strength():
                if random.randint(0, 1) == 0:
                    self.add_feed(collider, self)
                    new_x, new_y = self.get_position()
                    collider.set_position(new_x, new_y)
                    self.get_world().kill_organism(self)
                else:
                    log = "A has run away from "
                    log += collider.draw()
                    self.get_world().set_feed(log)
                    self.action()
            else:
                self.add_feed(self, collider)
                self.get_world().kill_organism(collider)
        else:
            self.reproduce()

    def new_position(self):
        new_x, new_y = self.get_position()
        index = random.randint(0, 1)
        prob = random.randint(0, 1)
        val = random.randint(1, 2)

        if index == 0:
            if prob == 0:
                new_x += val
            else:
                new_x -= val
        else:
            if prob == 0:
                new_y += val
            else:
                new_y -= val

        if 0 <= new_x < self.get_world().get_width() and 0 <= new_y < self.get_world().get_height():
            return new_x, new_y
        else:
            return False, False

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                a = Antelope(self.get_world(), new_x, new_y)
                self.get_world().add_organism(a)
