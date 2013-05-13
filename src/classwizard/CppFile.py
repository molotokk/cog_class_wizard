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

code_separator = '//-----------------------------------------------------------------------------'
braces = '{\n\n}\n'


class CppFile(GeneratorBase):
    def __init__(self, config_file):
        GeneratorBase.__init__(self, config_file)

    def generate(self):
        #print "Generating"

        if 'class' in self.config.keys():
            self.__generate_class_start(self.config)

            if 'private_data' in self.config.keys():
                self.__generate_data(self.config)

            self.__generate_class_body(self.config)

            if 'properties' in self.config.keys():
                self.__generate_properties(self.config)

            if 'methods' in self.config.keys():
                self.__generate_methods(self.config)

        return

    def __generate_class_start(self, config):
        class_name = config['class']
        cog.outl("#include %s.h" % class_name)
        cog.out("\n")
        return

    def __generate_properties(self, config):
        cog.outl("// PROPERTIES")
        for item in config['properties']:
            name = item['name']
            returns = tryRead(item, 'returns')
            modifies = tryRead(item, 'modifies')
            cog.outl(code_separator)

            #setter
            cog.outl("void %s::set%s(const %s value)" % (self.class_name, firstUppper(name), returns))
            if modifies:
                cog.outl('{\n\td_data->%s = value;\n}' % modifies)
            else:
                cog.outl(braces)

            #getter
            cog.outl("%s\t%s::%s() const" % (returns, self.class_name, name))
            if modifies:
                cog.outl('{\n\treturn d_data->%s;\n}' % modifies)
            else:
                cog.outl(braces)

        return

    def __generate_methods(self, config):
        vis_list = ['public', 'private', 'protected']

        for visibility in vis_list:
            cog.outl('// %s METHODS' % visibility.upper())
            for item in dictlistSelect(config['methods'], 'visibility', visibility):
                name = item['name']
                returns = tryRead(item, 'returns')
                arguments = tryRead(item, 'arguments')
                cog.outl(code_separator)
                cog.outl("%s\t%s::%s(%s)" % (returns, self.class_name, name, arguments))
                cog.outl(braces)
        return

    def __generate_data(self, config):
        cog.outl("class %s::%s\n{" % (self.class_name, self.data_name))
        cog.outl("\t\tpublic:")

        for item in config['private_data']:
            name = item['name']
            returns = tryRead(item, 'returns')
            cog.outl("\t\t%s\t%s;" % (returns, name))

        cog.outl('\t\t%s():' % self.data_name)
        first = True
        for item in config['private_data']:
            name = item['name']
            default = tryRead(item, 'default')
            if first:
                cog.out("\t\t\t%s(%s)" % (name, default))
                first = False
            else:
                cog.out("\n\t\t\t, %s(%s)" % (name, default))

        cog.outl('{\n\t\t}')

        cog.outl("};\n")
        return

    def __generate_class_body(self, config):
        cog.outl(code_separator)
        data_str = ''
        if 'private_data' in config.keys():
            data_str = " : d_data(new %s())" % self.data_name
        cog.outl("%s::%s() %s" % (self.class_name, self.class_name, data_str))
        cog.outl(braces)
        cog.outl("%s::~%s()" % (self.class_name, self.class_name))
        cog.outl(braces)

        return


if __name__ == '__main__':
    config_file = "../../simple_test/PanSharpener.yml"
    generator = CppFile(config_file)
    generator.generate("../../simple_test/PanSharpener.cpp")
    print(cog.outstring)

    #print "Generation done."