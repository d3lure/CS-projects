from OrganismModule import Organism
from abc import ABC, abstractmethod
import random


class Plant(Organism, ABC):

    def __init__(self, world, x, y, sign, stren, age):
        super().__init__(world, x, y, sign, 0, stren, age)

    @abstractmethod
    def reproduce(self):
        pass

    def action(self):
        if random.randint(1, 100) < 20:
            self.reproduce()

    def collision(self, collider):
        if type(self) != type(collider):
            if collider.get_strength() >= self.get_strength():
                self.get_world().kill_organism(self)
                collider.set_position(self.get_x(), self.get_y())
            else:
                self.add_feed(self, collider)
                self.get_world().kill_organism(collider)
                self.get_world().kill_organism(self)
