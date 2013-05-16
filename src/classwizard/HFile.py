#!/usr/bin/env python

from GeneratorBase import GeneratorBase
from util import firstUppper, dictlistSelect, tryRead
import cog

# ## Test code, comment when done
# from SimpleCog import CogGenerator
# import sys
# cog = CogGenerator()
# cog.setOutput(stdout=sys.stdout)
# ##

class Visibility():
    def __init__(self):
        self.state = ''

    def set(self, state):
        if state == self.state:
            pass
        else:
            cog.outl("\n\t%s:" % state)
            self.state = state

    def get(self):
        return self.state

class HFile(GeneratorBase):
    def __init__(self, config_file):
        GeneratorBase.__init__(self, config_file)
        self.vis = Visibility()


    def generate(self):
        #print "Generating "

        if 'class' in self.config.keys():
            self.__generate_class_start(self.config)

            if 'properties' in self.config.keys():
                self.__generate_properties(self.config)
            if 'methods' in self.config.keys():
                self.__generate_methods(self.config)
            if 'private_data' in self.config.keys():
                self.__generate_data(self.config)

            self.__generate_class_end(self.config)

        #return ''.join([class_code_start, property_code, method_code, data_code, class_code_end])
        return

    def __generate_class_start(self, config):
        class_name = config['class']
        cog.outl("#ifndef %s_H" % class_name.upper())
        cog.outl("#define %s_H" % class_name.upper())
        cog.out("\n\n\n")
        cog.outl("class %s\n{" % class_name)
        return

    def __generate_properties(self, config):
        self.vis.set('public')
        cog.outl("\t\t// Property get / set")
        for item in config['properties']:
            name = item['name']
            returns = tryRead(item, 'returns')
            cog.outl("\t\tvoid set%s(const %s value);" % (firstUppper(name), returns))
            cog.outl("\t\t%s\t%s() const;\n" % (returns, name))
        return

    def __generate_methods(self, config):
        cog.outl("\t\t// Methods")
        vis_list = ['public', 'private', 'protected']
        for visibility in vis_list:
            self.vis.set(visibility)
            for item in dictlistSelect(config['methods'], 'visibility', visibility):
                name = item['name']
                returns = tryRead(item, 'returns')
                arguments = tryRead(item, 'arguments')
                modifier = tryRead(item, 'modifier')
                cog.outl("\t\t%s\t%s(%s) %s;" % (returns, name, arguments, modifier))
        return

    def __generate_data(self, config):
        self.vis.set('private')
        cog.outl("\t\tclass\t%s;" % self.data_name)
        cog.outl("\t\tstd::unique_ptr<%s>\td_data;" % self.data_name)
        return

    def __generate_class_end(self, config):
        class_name = config['class']
        self.vis.set('public')
        cog.outl("\t\t%s();" % class_name)
        cog.outl("\t\tvirtual ~%s();" % class_name )
        cog.outl("};\n\n#endif //%s_H" % class_name.upper())
        return


if __name__ == '__main__':
    config_file = "../../tests/PanSharpener.yml"
    generator = HFile(config_file)
    generator.generate()
    print(cog.outstring)

    #print "Generation done."