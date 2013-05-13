#!/usr/bin/env python

class Generator():
    def __init__(self, filename):
        self.filename = filename
        return

    def run(self):
        return

if __name__ == '__main__':
    generator = Generator("./simple_test/PanSharpener.yml")
    generator.run()
    print "Generation done."


