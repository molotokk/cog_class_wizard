#!/usr/bin/env python

from GeneratorBase import GeneratorBase
from common import generate_cppclass_common
from util import sanitizeTypename, indent
import cog

def firstUppper(str):
    return str[0].upper() + str[1:]

class CppClass(GeneratorBase):
    def __init__(self, name, fields, config={}):
        GeneratorBase.__init__(self, name, fields, config)

    def __gen_for_all_members(self):
        pass

    def generate(self):  # H - File

        cog.out("#ifndef %s_H\n" % self.name.upper())
        cog.out("#define %s_H\n" % self.name.upper())
        cog.out("\n\n\n")
        cog.out("class %s\n{\n" % self.name)

        # Write Properties
        cog.out("\tpublic:")
        cog.out("\t\t// Property get / set\n")

        for f in self.fields:
            if f.type:
                cog.out("\t\tvoid set%s(const %s value);\n" % (firstUppper(f.name), f.type))
                cog.out("\t\t%s\t%s() const;\n" % ( f.type, f.name))

        # Write methods
        # TODO

        cog.out("};\n\n#endif %s_H\n" % self.name.upper() )

