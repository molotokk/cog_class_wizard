#!/usr/bin/env python

import os
import yaml


class ConfigReader():
    def __init__(self, filename):
        self.filename = filename
        return

    # def read(self):
    #     self.read(self.filename)

    def read(self):
        if not os.path.exists(self.filename):
            raise Exception("File doesn't exist : " + filename)

        f = open(self.filename, 'rb')
        config = yaml.safe_load(f.read())
        # print tmp
        return config


if __name__ == '__main__':
    configReader = ConfigReader("./simple_test/PanSharpener.yml")
    config = configReader.read()
    print config