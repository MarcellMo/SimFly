function blkStruct = slblocks
     %% HiliShield library
     %% Author: Marcell Mocher
     % Date_: 02.12.2015 
%   Copyright 2012-2014 The MathWorks, Inc.

        blkStruct.Name = 'SimFly'; %Display name
        blkStruct.OpenFcn = 'SimFly_library'; %Library name
        blkStruct.MaskDisplay = '';
        Browser(1).Library = 'SimFly_library'; %Library name
		% This function specifies that the library should appear
		% in the Library Browser
		% and be cached in the browser repository


		Browser(1).Name = 'SimFly';
		% 'My Library' is the library name that appears in the Library Browser

		blkStruct.Browser = Browser;