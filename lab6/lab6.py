class HashTable:
    def __init__(self):
        self.size = 20
        self.table = [[] for _ in range(self.size)]

    def _get_hash(self, key):
        hash_value = 0
        for char in str(key):
            hash_value += ord(char)
        return hash_value % self.size

    def add_item(self, key, value):
        hash_key = self._get_hash(key)
        for item in self.table[hash_key]:
            if item[0] == key:
                item[1] = value
                return
        self.table[hash_key].append((key, value))

    def remove_item(self, key):
        hash_key = self._get_hash(key)
        for idx, item in enumerate(self.table[hash_key]):
            if item[0] == key:
                del self.table[hash_key][idx]
                return

    def get_item(self, key):
        hash_key = self._get_hash(key)
        for item in self.table[hash_key]:
            if item[0] == key:
                return item[1]
        return None

    def display(self):
        for i in range(self.size):
            for item in self.table[i]:
                print(f"{i} : {item[0]} : {item[1]}")


def main():
    hash_table = HashTable()

    hash_table.add_item("derivative", "a mathematical concept that represents the rate of change of a function")
    hash_table.add_item("integral", "a mathematical concept that represents the area under a curve")
    hash_table.add_item("vector", "a mathematical concept that represents a quantity with both magnitude and direction")
    hash_table.add_item("matrix", "a mathematical concept that represents a collection of numbers arranged in a grid")
    hash_table.add_item("function", "a mathematical concept that represents a relationship between two variables")
    hash_table.add_item("theorem", "a mathematical concept that represents a statement that has been proven to be true")
    hash_table.add_item("algorithm",
                        "a mathematical concept that represents a set of instructions for solving a problem")
    hash_table.add_item("equation",
                        "a mathematical concept that represents a statement of equality between two expressions")
    hash_table.add_item("geometry",
                        "a mathematical concept that represents the study of shapes, sizes, and positions of objects")
    hash_table.add_item("probability", "a mathematical concept that represents the likelihood of an event occurring")

    print("Содержимое таблицы:")
    hash_table.display()

    print("\nСодержимое таблицы после удаления элементов:")
    hash_table.remove_item("equation")
    hash_table.remove_item("derivative")
    hash_table.remove_item("probability")
    hash_table.display()

    key_for_display = "vector"
    print("\nВывод информации по ключу", key_for_display + ":")
    print(hash_table.get_item(key_for_display))


main()
