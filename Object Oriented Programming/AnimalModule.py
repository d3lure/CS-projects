from OrganismModule import Organism
from abc import ABC, abstractmethod
from NullModule import Null


class Animal(Organism, ABC):

    def __init__(self, world, x, y, sign, init, stren, age):
        super().__init__(world, x, y, sign, init, stren, age)

    def action(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                self.set_position(new_x, new_y)
            else:
                self.get_board()[new_x][new_y].collision(self)
        #else:
         #   print(f"{self.draw()} failed to make a move at {self.get_position()}")

    def collision(self, collider):
        if type(self) != type(collider):
            if collider.get_strength() >= self.get_strength():
                self.add_feed(collider, self)
                self.get_world().kill_organism(self)
                collider.set_position(self.get_x(), self.get_y())
            else:
                if isinstance(collider, Animal):
                    self.add_feed(self, collider)
                self.get_world().kill_organism(collider)
        else:
            self.reproduce()

    @abstractmethod
    def reproduce(self):
        pass


