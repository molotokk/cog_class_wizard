#!/usr/bin/env python

import os
import yaml


class ConfigReader():
    def __init__(self):
        return

    def read(self, filename):
        if not os.path.exists(filename):
            raise Exception("File doesn't exist : " + filename)

        f = open(filename, 'rb')
        config = yaml.safe_load(f.read())
        # print tmp
        return config


if __name__ == '__main__':
    configReader = ConfigReader()
    config = configReader.read("./simple_test/PanSharpener.yml")
    print config