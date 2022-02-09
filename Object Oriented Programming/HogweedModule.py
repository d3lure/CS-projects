import random
from PlantModule import Plant
from NullModule import Null
from AnimalModule import Animal
from HumanModule import Human
from CyberSheepModule import CyberSheep


class Hogweed(Plant):
    def __init__(self, world, x, y, stren=10, age=0):
        super(Hogweed, self).__init__(world, x, y, '!', stren, age)
        self._neighbours = []

    def set_neighbours(self):
        self._neighbours.clear()
        x, y = self.get_position()
        positions = []

        pos1 = [x + 1, y]
        pos2 = [x - 1, y]
        pos3 = [x, y + 1]
        pos4 = [x, y - 1]

        positions.append(pos1)
        positions.append(pos2)
        positions.append(pos3)
        positions.append(pos4)

        for pos in positions:
            if 0 <= pos[0] < self.get_world().get_width():
                if 0 <= pos[1] < self.get_world().get_height():
                    field = self.is_empty(pos[0], pos[1])
                    if field != Null and not isinstance(field, CyberSheep):
                        self._neighbours.append(field)

    def action(self):
        self.set_neighbours()
        for org in self._neighbours:
            if isinstance(org, Animal):
                if not isinstance(org, Human):
                    self.add_feed(self, org)
                    self.get_world().kill_organism(org)
                    self._neighbours.remove(org)
                else:
                    if self.get_world().get_human().is_immortal() is False:
                        self.get_world().set_human(None)
                        self.add_feed(self, org)
                        self.get_world().kill_organism(org)
                        self._neighbours.remove(org)

        if random.randrange(100) < 10:
            self.reproduce()

    def collision(self, collider):
        if type(self) != type(collider):
            if isinstance(collider, CyberSheep):
                self.get_world().kill_organism(self)
                collider.set_position(self.get_x(), self.get_y())

            elif isinstance(collider, Human) and \
                    self.get_world().get_human().is_immortal():
                pass

            else:
                self.get_world().kill_organism(collider)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            empty = self.is_empty(new_x,  new_y)
            if empty is True:
                h = Hogweed(self.get_world(), new_x, new_y)
                self.get_world().add_organism(h)
