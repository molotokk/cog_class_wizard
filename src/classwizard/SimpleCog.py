#!/usr/bin/env python

from __future__ import print_function
import os, sys

class Redirectable:
    """ An object with its own stdout and stderr files.
    """
    def __init__(self):
        self.stdout = sys.stdout
        self.stderr = sys.stderr

    def setOutput(self, stdout=None, stderr=None):
        """ Assign new files for standard out and/or standard error.
        """
        if stdout:
            self.stdout = stdout
        if stderr:
            self.stderr = stderr

    def prout(self, s, end="\n"):
        print(s, file= self.stdout, end=end)

    def prerr(self, s, end="\n"):
        print(s, file= self.stderr, end=end)



class CogGenerator(Redirectable):
    def __init__(self):
        Redirectable.__init__(self)
        #self.output_file = output_file
        #self.file = os.open(output_file, 'wb')
        self.outstring = ''

        return

    def msg(self, s):
        self.prout("Message: "+s)

    def out(self, sOut='', dedent=False, trimblanklines=False):
        """ The cog.out function.
        """
        if trimblanklines and ('\n' in sOut):
            lines = sOut.split('\n')
            if lines[0].strip() == '':
                del lines[0]
            if lines and lines[-1].strip() == '':
                del lines[-1]
            sOut = '\n'.join(lines)+'\n'

        self.outstring += sOut
        return

    def outl(self, sOut='', **kw):
        """ The cog.outl function.
        """
        self.out(sOut, **kw)
        self.out('\n')
        return

    def error(self, msg='Error raised by cog generator.'):
        """ The cog.error function.
            Instead of raising standard python errors, cog generators can use
            this function.  It will display the error without a scary Python
            traceback.
        """
        raise Exception(msg)
