#!/usr/bin/env python

from ConfigReader import ConfigReader
from util import tryRead, verifyName



class GeneratorBase():
    def __init__(self, config_file):
        self.config_file = config_file   # an yml file
        configReader = ConfigReader()
        self.config = configReader.read(self.config_file)   # is a dict of lists of dicts (see yml file structure)
        self.class_name = ''
        self.data_name = 'PrivateData'

        # Verify all names
        for key, value in self.config.items():
            if key == 'class':
                #print value
                verifyName(value)
                self.class_name = value

            else:     # methods, properties,  private_data
                for item in value:
                    #print item['name']
                    verifyName(item['name'])  # TODO: check for duplicates

        # Retrieve private data names
        private_data_names = []
        if 'private_data' in self.config.keys():
            dictlist = self.config['private_data']
            private_data_names = [dictio['name'] for dictio in dictlist]

        #print private_data_names

        # Check if a property refers to a non-existing data field
        if 'properties' in self.config.keys():
            for item in self.config['properties']:
                referred_data = tryRead(item,'modifies')
                if referred_data and referred_data not in private_data_names:
                    print ('%s property modifies %s private_data field. Autocreating.' %
                           (item['name'], item['modifies']))
                    # Add private data field
                    #print item
                    if not 'private_data' in self.config.keys():
                        self.config['private_data'] = []
                    self.config['private_data'].append({'name':item['name'], 'returns':item['returns'], 'default':''})

        return



    def generate(self):
        pass

if __name__ == '__main__':
    #config_file = "../../tests/PanSharpener.yml"
    config_file = "../../tests/test.yml"
    generator = GeneratorBase(config_file)

    #print "Generation done."
