// -----------------------------------------------
// resourcemanager.spec.js
//
// test suite for ResourceManager
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

describe("ResourceManager", function() {

  var resourceManager;
  var dataRefNum;
  var testRefNum;

  beforeEach(function() {
    resourceManager = pdg.res;
    expect(resourceManager).toBeDefined();
  });

  afterEach(function() {
    // Clean up any opened resource files
    if (dataRefNum && dataRefNum !== 0) {
      try {
        resourceManager.closeResourceFile(dataRefNum);
      } catch (e) {
        // Ignore cleanup errors
      }
    }
    if (testRefNum && testRefNum !== 0) {
      try {
        resourceManager.closeResourceFile(testRefNum);
      } catch (e) {
        // Ignore cleanup errors
      }
    }
  });

  describe("Singleton Access", function() {
    it("is a singleton accessed by pdg.res", function() {
      console.log('* Testing ResourceManager...');
      var res = pdg.res;
      expect(res).toBeDefined();
      var res2 = pdg.getResourceManager();
      expect(res).toBe(res2);
    });

    it("returns the same instance via different access methods", function() {
      var res1 = pdg.res;
      var res2 = pdg.getResourceManager();
      var res3 = pdg.res;
      
      expect(res1).toBe(res2);
      expect(res2).toBe(res3);
      expect(res1).toBe(res3);
    });

    it("has the correct constructor name", function() {
      expect(resourceManager.constructor.name).toBe('ResourceManager');
    });
  });

  describe("Language Management", function() {
    it("can get current language", function() {
      var language = resourceManager.getLanguage();
      expect(language).toBeDefined();
      expect(typeof language).toBe('string');
      // Language might be empty string by default
    });

    it("can set language", function() {
      var originalLanguage = resourceManager.getLanguage();
      
      var result = resourceManager.setLanguage('es');
      expect(result).toBe(resourceManager);
      
      var newLanguage = resourceManager.getLanguage();
      expect(newLanguage).toBe('es');
      
      // Restore original language
      resourceManager.setLanguage(originalLanguage);
    });

    it("can set different languages", function() {
      var languages = ['en', 'es', 'fr', 'de'];
      
      languages.forEach(function(lang) {
        var result = resourceManager.setLanguage(lang);
        expect(result).toBe(resourceManager);
        
        var currentLanguage = resourceManager.getLanguage();
        expect(currentLanguage).toBe(lang);
      });
    });

    it("can set language with empty string", function() {
      var result = resourceManager.setLanguage('');
      expect(result).toBe(resourceManager);
      
      var language = resourceManager.getLanguage();
      expect(language).toBe('');
    });

    it("can set language with special characters", function() {
      var specialLanguages = ['en-US', 'es-ES', 'zh-CN'];
      
      specialLanguages.forEach(function(lang) {
        var result = resourceManager.setLanguage(lang);
        expect(result).toBe(resourceManager);
        
        var currentLanguage = resourceManager.getLanguage();
        expect(currentLanguage).toBe(lang);
      });
    });
  });

  describe("Resource File Management", function() {
    it("can open resource file", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      expect(typeof dataRefNum).toBe('number');
      expect(dataRefNum !== 0).toBe(true);
    });

    it("can open multiple resource files", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      testRefNum = resourceManager.openResourceFile('spec');
      
      expect(typeof dataRefNum).toBe('number');
      expect(typeof testRefNum).toBe('number');
      expect(dataRefNum !== 0).toBe(true);
      expect(testRefNum !== 0).toBe(true);
      expect(dataRefNum !== testRefNum).toBe(true);
    });

    it("can close resource file", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      expect(dataRefNum !== 0).toBe(true);
      
      expect(function() {
        resourceManager.closeResourceFile(dataRefNum);
      }).not.toThrow();
      
      dataRefNum = 0; // Mark as closed
    });

    it("can open and close resource files multiple times", function() {
      for (var i = 0; i < 3; i++) {
        var refNum = resourceManager.openResourceFile('data');
        expect(refNum !== 0).toBe(true);
        
        resourceManager.closeResourceFile(refNum);
      }
    });

    it("handles opening non-existent resource files gracefully", function() {
      var refNum = resourceManager.openResourceFile('nonexistent');
      expect(typeof refNum).toBe('number');
      // Should return 0 or some error indicator for non-existent files
    });

    it("handles closing invalid reference numbers gracefully", function() {
      expect(function() {
        resourceManager.closeResourceFile(999);
      }).not.toThrow();
    });
  });

  describe("Resource Paths", function() {
    beforeEach(function() {
      dataRefNum = resourceManager.openResourceFile('data');
    });

    it("can get resource paths", function() {
      var paths = resourceManager.getResourcePaths();
      expect(typeof paths).toBe('string');
      expect(paths.length > 0).toBe(true);
    });

    it("returns consistent resource paths", function() {
      var paths1 = resourceManager.getResourcePaths();
      var paths2 = resourceManager.getResourcePaths();
      
      expect(paths1).toBe(paths2);
    });

    it("includes opened resource paths", function() {
      var paths = resourceManager.getResourcePaths();
      expect(paths).toContain('/data/');
    });

    it("updates paths when files are closed", function() {
      var pathsBefore = resourceManager.getResourcePaths();
      expect(pathsBefore).toContain('/data/');
      
      resourceManager.closeResourceFile(dataRefNum);
      dataRefNum = 0;
      
      var pathsAfter = resourceManager.getResourcePaths();
      expect(pathsAfter).not.toContain('/data/');
    });
  });

  describe("String Resources", function() {
    beforeEach(function() {
      dataRefNum = resourceManager.openResourceFile('data');
    });

    it("can get strings by ID", function() {
      var str200 = resourceManager.getString(200);
      var str300 = resourceManager.getString(300);
      
      expect(typeof str200).toBe('string');
      expect(typeof str300).toBe('string');
      expect(str200.length > 0).toBe(true);
      expect(str300.length > 0).toBe(true);
    });

    it("can get specific known strings", function() {
      var str200 = resourceManager.getString(200);
      var str500 = resourceManager.getString(500);
      
      expect(str200).toContain('Grain|grain.png');
      expect(str500).toContain('There is no zip version of this string');
    });

    it("can get strings with substring parameter", function() {
      var str300 = resourceManager.getString(300);
      var str300Sub = resourceManager.getString(300, 0);
      
      expect(typeof str300).toBe('string');
      expect(typeof str300Sub).toBe('string');
    });

    it("handles non-existent string IDs gracefully", function() {
      var str = resourceManager.getString(999999);
      expect(typeof str).toBe('string');
      // Should return empty string or some default for non-existent IDs
    });

    it("handles negative string IDs gracefully", function() {
      var str = resourceManager.getString(-1);
      expect(typeof str).toBe('string');
    });

    it("handles zero string ID gracefully", function() {
      var str = resourceManager.getString(0);
      expect(typeof str).toBe('string');
    });
  });

  describe("Localized Strings", function() {
    beforeEach(function() {
      dataRefNum = resourceManager.openResourceFile('data');
    });

    it("can get localized strings in Spanish", function() {
      resourceManager.setLanguage('es');
      
      var str200 = resourceManager.getString(200);
      var str500 = resourceManager.getString(500);
      
      expect(str200).toContain('Granos|grain.png');
      expect(str500).toContain('No hay versión zip de este mensaje');
    });

    it("can get localized strings in different languages", function() {
      // Test English
      resourceManager.setLanguage('en');
      var str200En = resourceManager.getString(200);
      expect(str200En).toContain('Grain|grain.png');
      
      // Test Spanish
      resourceManager.setLanguage('es');
      var str200Es = resourceManager.getString(200);
      expect(str200Es).toContain('Granos|grain.png');
      
      // Test that they're different
      expect(str200En).not.toBe(str200Es);
      
      // Restore original language
      resourceManager.setLanguage('en');
    });

    it("falls back gracefully for missing translations", function() {
      resourceManager.setLanguage('es');
      
      var str501 = resourceManager.getString(501);
      expect(str501).toContain('There is no Spanish or zip version of this string');
    });

    it("maintains language setting across multiple calls", function() {
      resourceManager.setLanguage('es');
      
      for (var i = 0; i < 3; i++) {
        var str200 = resourceManager.getString(200);
        expect(str200).toContain('Granos|grain.png');
      }
    });
  });

  describe("Image Resources", function() {
    beforeEach(function() {
      dataRefNum = resourceManager.openResourceFile('data');
    });
    afterEach(function() {
      resourceManager.closeResourceFile(dataRefNum);
    });

    it("can get image by name", function() {
      var image = resourceManager.getImage('earthmap2.jpg');
      expect(image).not.toBeNull();
      expect(image.constructor.name === 'Image').toBe(true);
    });

    it("can get image strip by name", function() {
      var imageStrip = resourceManager.getImageStrip('rocks.png');
      expect(imageStrip).not.toBeNull();
      expect(imageStrip.constructor.name === 'ImageStrip').toBe(true);
    });

    it("handles non-existent images gracefully", function() {
      var image = resourceManager.getImage('nonexistent.png');
      expect(image).toBeNull();
    });

    it("handles non-existent image strips gracefully", function() {
      var imageStrip = resourceManager.getImageStrip('nonexistent.png');
      expect(imageStrip).toBeNull();
    });

    it("can get images with different extensions", function() {
      var pngImage = resourceManager.getImage('test_image.png');
      var jpgImage = resourceManager.getImage('earthmap2.jpg');
      
      expect(pngImage).not.toBeNull();
      expect(pngImage.constructor.name === 'Image').toBe(true);
      expect(jpgImage).not.toBeNull();
      expect(jpgImage.constructor.name === 'Image').toBe(true);
    });
  });

  describe("Resource Size and Data", function() {
    beforeEach(function() {
      dataRefNum = resourceManager.openResourceFile('data');
    });

    it("can get resource size", function() {
      var expectedSize = fs.readFileSync('data/strings.txt').length;
      var size = resourceManager.getResourceSize('strings.txt');
      expect(typeof size).toBe('number');
      expect(size > 0).toBe(true);
	  expect(size).toBe(expectedSize);
    });

    it("can get resource data", function() {
      var data = resourceManager.getResource('strings.txt');
      expect(typeof data).toBe('string');
      expect(data.length > 0).toBe(true);
    });

    it("handles non-existent resources gracefully", function() {
      var size = resourceManager.getResourceSize('nonexistent.txt');
      var data = resourceManager.getResource('nonexistent.txt');
      
      expect(typeof size).toBe('number');
      // getResource might return boolean or string depending on implementation
      expect(typeof data === 'string' || typeof data === 'boolean').toBe(true);
      // Should return 0 for size and empty string or false for data
    });

    it("returns consistent resource sizes", function() {
      var size1 = resourceManager.getResourceSize('strings.txt');
      var size2 = resourceManager.getResourceSize('strings.txt');
      
      expect(size1).toBe(size2);
    });

    it("returns consistent resource data", function() {
      var data1 = resourceManager.getResource('strings.txt');
      var data2 = resourceManager.getResource('strings.txt');
      
      expect(data1).toBe(data2);
    });
  });

  describe("Error Handling", function() {
    beforeEach(function() {
      // needed for test because otherwise we'll get an assert trying to use
      // resources without a resource file open
      dataRefNum = resourceManager.openResourceFile('data');
    });
    afterEach(function() {
      resourceManager.closeResourceFile(dataRefNum);
    });

    it("won't load resources outside of the resource directories", function() {
      var image = resourceManager.getImage('../jupitermap.jpg');
      expect(image).toBeFalsy();
      var imageStrip = resourceManager.getImageStrip('../tiles.png');
      expect(imageStrip).toBeFalsy();
      //var sound = resourceManager.getSound('../sound.wav');
      //expect(sound).toBeFalsy();
      var size = resourceManager.getResourceSize('../strings.txt');
      expect(size).toBe(0);
      var data = resourceManager.getResource('../strings.txt');
      expect(data).toBeFalsy();
    });

    it("handles null and undefined parameters gracefully", function() {
      console.log('  - Error Handling');
      expect(function() {
        resourceManager.setLanguage(null); // docs introspection
      }).not.toThrow();
      
      expect(function() {
        resourceManager.setLanguage(undefined);
      }).toThrow();
      
      expect(function() {
        resourceManager.openResourceFile(null); // docs introspection
      }).not.toThrow();
      
      expect(function() {
        resourceManager.openResourceFile(undefined);
      }).toThrow();
    });

    it("handles empty string parameters gracefully", function() {
      expect(function() {
        resourceManager.setLanguage('');
      }).not.toThrow();
      
      expect(function() {
        resourceManager.openResourceFile('');
      }).not.toThrow();
    });

    it("handles very long resource names gracefully", function() {
      var longName = 'a'.repeat(1000) + '.txt';
      expect(function() {
        resourceManager.getResourceSize(longName);
      }).not.toThrow();
      
      expect(function() {
        resourceManager.getResource(longName);
      }).not.toThrow();
    });

    it("handles special characters in resource names gracefully", function() {
      var specialNames = [
        'test file.txt',
        'test-file.txt',
        'test_file.txt',
        'test.file.txt',
        'test!@#$%^&*().txt'
      ];
      
      specialNames.forEach(function(name) {
        expect(function() {
          resourceManager.getResourceSize(name);
        }).not.toThrow();
        
        expect(function() {
          resourceManager.getResource(name);
        }).not.toThrow();
      });
    });
  });

  describe("Performance and Scalability", function() {
    it("can handle rapid language changes", function() {
      console.log('  - Performance and Scalability');
      var languages = ['en', 'es', 'fr', 'de'];
      
      for (var i = 0; i < 10; i++) {
        languages.forEach(function(lang) {
          var result = resourceManager.setLanguage(lang);
          expect(result).toBe(resourceManager);
        });
      }
    });

    it("can handle rapid resource file operations", function() {
      for (var i = 0; i < 5; i++) {
        var refNum = resourceManager.openResourceFile('data');
        expect(refNum !== 0).toBe(true);
        
        resourceManager.closeResourceFile(refNum);
      }
    });

    it("can handle multiple simultaneous resource files", function() {
      var refNums = [];
      
      // Open multiple resource files
      for (var i = 0; i < 3; i++) {
        var refNum = resourceManager.openResourceFile('data');
        refNums.push(refNum);
        expect(refNum !== 0).toBe(true);
      }
      
      // Close all resource files
      refNums.forEach(function(refNum) {
        resourceManager.closeResourceFile(refNum);
      });
    });
  });

  describe("Integration Tests", function() {
    it("can manage resources with language changes", function() {
      console.log('  - Integration Tests');
      dataRefNum = resourceManager.openResourceFile('data');
      
      // Test English strings
      resourceManager.setLanguage('en');
      var str200En = resourceManager.getString(200);
      expect(str200En).toContain('Grain|grain.png');
      
      // Test Spanish strings
      resourceManager.setLanguage('es');
      var str200Es = resourceManager.getString(200);
      expect(str200Es).toContain('Granos|grain.png');
      
      // Test image loading
      var image = resourceManager.getImage('grain.png');
      expect(image).toBeDefined();
      
      // Test resource data
      var data = resourceManager.getResource('strings.txt');
      expect(data.length > 0).toBe(true);
    });

    it("can manage multiple resource files simultaneously", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      testRefNum = resourceManager.openResourceFile('spec');
      
      var paths = resourceManager.getResourcePaths();
      expect(paths).toContain('/data/');
      expect(paths).toContain('/spec/');
      
      // Test string retrieval - ensure we're in English mode
      resourceManager.setLanguage('en');
      var str200 = resourceManager.getString(200);
      expect(str200).toContain('Grain|grain.png');
      
      // Test image retrieval
      var image = resourceManager.getImage('tiles.png');
      expect(image).toBeDefined();
    });

    it("can handle resource lifecycle", function() {
      // Open resource file
      dataRefNum = resourceManager.openResourceFile('data');
      expect(dataRefNum !== 0).toBe(true);
      
      // Get resource paths
      var paths = resourceManager.getResourcePaths();
      expect(paths).toContain('/data/');
      
      // Get string resources - ensure we're in English mode
      resourceManager.setLanguage('en');
      var str200 = resourceManager.getString(200);
      expect(str200).toContain('Grain|grain.png');
      
      // Change language
      resourceManager.setLanguage('es');
      var str200Es = resourceManager.getString(200);
      expect(str200Es).toContain('Granos|grain.png');
      
      // Get image resources
      var image = resourceManager.getImage('grain.png');
      expect(image).toBeDefined();
      
      // Get resource data
      var data = resourceManager.getResource('strings.txt');
      expect(data.length > 0).toBe(true);
      
      // Close resource file
      resourceManager.closeResourceFile(dataRefNum);
      dataRefNum = 0;
      
      // Verify resource file is closed
      var pathsAfter = resourceManager.getResourcePaths();
      expect(pathsAfter).not.toContain('/data/');
    });
  });

  describe("Validation", function() {
    it("validates that getLanguage returns string", function() {
      console.log('  - Validation');
      var language = resourceManager.getLanguage();
      expect(typeof language).toBe('string');
    });

    it("validates that setLanguage returns ResourceManager", function() {
      var result = resourceManager.setLanguage('en');
      expect(result).toBe(resourceManager);
    });

    it("validates that openResourceFile returns number", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      expect(typeof dataRefNum).toBe('number');
    });

    it("validates that getResourcePaths returns string", function() {
      var paths = resourceManager.getResourcePaths();
      expect(typeof paths).toBe('string');
    });

    it("validates that getString returns string", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      var str = resourceManager.getString(200);
      expect(typeof str).toBe('string');
    });

    it("validates that getImage returns Image or null", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      var image = resourceManager.getImage('grain.png');
      expect(image === null || image === undefined || typeof image === 'boolean' || image.constructor.name === 'Image').toBe(true);
    });

    it("validates that getResourceSize returns number", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      var size = resourceManager.getResourceSize('strings.txt');
      expect(typeof size).toBe('number');
    });

    it("validates that getResource returns string", function() {
      dataRefNum = resourceManager.openResourceFile('data');
      var data = resourceManager.getResource('strings.txt');
      expect(typeof data).toBe('string');
    });

    it("validates consistency across multiple calls", function() {
      var language1 = resourceManager.getLanguage();
      var language2 = resourceManager.getLanguage();
      expect(language1).toBe(language2);
      
      var paths1 = resourceManager.getResourcePaths();
      var paths2 = resourceManager.getResourcePaths();
      expect(paths1).toBe(paths2);
    });
  });

});
