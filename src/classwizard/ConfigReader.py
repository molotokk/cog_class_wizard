#!/usr/bin/env python

import os
import yaml
import re


class ConfigReader():
    def __init__(self):
        self.string = None

    def read(self, filename):
        if not os.path.exists(filename):
            raise Exception("File doesn't exist : " + filename)

        f = open(filename, 'rb')
        pattern = re.compile(r'\t')
        self.string = re.sub(pattern, '    ', f.read())
        config = yaml.safe_load(self.string)
        # print config
        return config

    def write(self, filename):
        f = open(filename, 'wb')
        f.write(self.string)
        return


if __name__ == '__main__':
    configReader = ConfigReader()
    config = configReader.read("./tests/PanSharpener.yml")
    configReader.write("./tests/PanSharpener_new.yml")
    print config