#!/usr/bin/env python

from ConfigReader import ConfigReader
from util import verifyName



class GeneratorBase():
    def __init__(self, config_file):
        self.config_file = config_file   # items is a dict read from a yaml file
        configReader = ConfigReader()
        self.config = configReader.read(self.config_file)
        self.class_name = ''
        self.data_name = 'PrivateData'

        for key, value in self.config.items():
            if key == 'class':
                #print value
                verifyName(value)
                self.class_name = value

            else:     # properties, methods, private_data
                for item in value:
                    #print item['name']
                    verifyName(item['name'])  # TODO: check for duplicates
                                              # TODO: warnings when no data exist but properties access them

        return



    def generate(self, output_file):
        print "Generating %s" % output_file
        return

if __name__ == '__main__':
    config_file = "../../simple_test/PanSharpener.yml"
    generator = GeneratorBase(config_file)
    generator.generate("../../simple_test/PanSharpener.yml")
    #print "Generation done."
