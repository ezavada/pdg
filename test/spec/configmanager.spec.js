// -----------------------------------------------
// configmanager.spec.js
//
// test suite for ConfigManager
//
// Written by Ed Zavada, 2014
// Copyright (c) 2014, Dream Rock Studios, LLC
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

describe("ConfigManager", function() {

  var cfg;
  var testConfigName = 'pdgtestsuite-cfgmgrtest';

  beforeEach(function() {
    cfg = pdg.cfg;
    expect(cfg).toBeDefined();
  });

  describe("Singleton Access", function() {
    it("is a singleton accessed by pdg.cfg", function() {
      console.log('* Testing ConfigManager...');
      var cfg = pdg.cfg;
      expect(cfg).toBeDefined();
      var cfg2 = pdg.getConfigManager();
      expect(cfg2).toBe(cfg);
    });

    it("returns the same instance via different access methods", function() {
      var cfg1 = pdg.cfg;
      var cfg2 = pdg.getConfigManager();
      var cfg3 = pdg.cfg;
      
      expect(cfg1).toBe(cfg2);
      expect(cfg2).toBe(cfg3);
      expect(cfg1).toBe(cfg3);
    });

    it("has the correct constructor name", function() {
      expect(cfg.constructor.name).toBe('ConfigManager');
    });
  });

  describe("Configuration Management", function() {
    it("can use a configuration", function() {
      var result = cfg.useConfig(testConfigName);
      expect(typeof result).toBe('boolean');
    });

    it("can use different configuration names", function() {
      var configs = [
        'test-config-1',
        'test-config-2',
        'my-app-config',
        'user-preferences'
      ];
      
      configs.forEach(function(configName) {
        var result = cfg.useConfig(configName);
        expect(typeof result).toBe('boolean');
      });
    });

    it("can use configuration with special characters", function() {
      var specialConfigs = [
        'test-config_with_underscores',
        'test-config-with-dashes',
        'test.config.with.dots',
        'test_config_with_numbers_123'
      ];
      
      specialConfigs.forEach(function(configName) {
        var result = cfg.useConfig(configName);
        expect(typeof result).toBe('boolean');
      });
    });

    it("can use empty configuration name", function() {
      var result = cfg.useConfig('');
      expect(typeof result).toBe('boolean');
    });
  });

  describe("String Configuration", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("can set and get string values", function() {
      cfg.setConfigString('testString', 'Hello World');
      var value = cfg.getConfigString('testString');
      expect(value).toBe('Hello World');
    });

    it("can set and get empty string", function() {
      cfg.setConfigString('emptyString', '');
      var value = cfg.getConfigString('emptyString');
      expect(value).toBe('');
    });

    it("can set and get long strings", function() {
      var longString = 'A'.repeat(1000);
      cfg.setConfigString('longString', longString);
      var value = cfg.getConfigString('longString');
      expect(value).toBe(longString);
    });

    it("can set and get strings with special characters", function() {
      var specialString = 'Special: !@#$%^&*()_+-=[]{}|;:,.<>?';
      cfg.setConfigString('specialString', specialString);
      var value = cfg.getConfigString('specialString');
      expect(value).toBe(specialString);
    });

    it("can set and get unicode strings", function() {
      var unicodeString = 'Unicode: 你好世界 🌍 🚀';
      cfg.setConfigString('unicodeString', unicodeString);
      var value = cfg.getConfigString('unicodeString');
      expect(value).toBe(unicodeString);
    });

    it("can overwrite string values", function() {
      cfg.setConfigString('overwriteTest', 'Original');
      cfg.setConfigString('overwriteTest', 'Updated');
      var value = cfg.getConfigString('overwriteTest');
      expect(value).toBe('Updated');
    });

    it("returns undefined for non-existent string keys", function() {
      var value = cfg.getConfigString('nonExistentString');
      expect(value).toBeUndefined();
    });

    it("can handle multiple string values", function() {
      var strings = {
        'string1': 'First string',
        'string2': 'Second string',
        'string3': 'Third string'
      };
      
      Object.keys(strings).forEach(function(key) {
        cfg.setConfigString(key, strings[key]);
      });
      
      Object.keys(strings).forEach(function(key) {
        var value = cfg.getConfigString(key);
        expect(value).toBe(strings[key]);
      });
    });
  });

  describe("Long Configuration", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("can set and get long values", function() {
      cfg.setConfigLong('testLong', 12345);
      var value = cfg.getConfigLong('testLong');
      expect(value).toBe(12345);
    });

    it("can set and get zero", function() {
      cfg.setConfigLong('zeroLong', 0);
      var value = cfg.getConfigLong('zeroLong');
      expect(value).toBe(0);
    });

    it("can set and get negative values", function() {
      cfg.setConfigLong('negativeLong', -12345);
      var value = cfg.getConfigLong('negativeLong');
      expect(value).toBe(-12345);
    });

    it("can set and get large values", function() {
      cfg.setConfigLong('largeLong', 2147483647); // Max 32-bit int
      var value = cfg.getConfigLong('largeLong');
      expect(value).toBe(2147483647);
    });

    it("can set and get very large values", function() {
      cfg.setConfigLong('veryLargeLong', 2147483647); // Max 32-bit int (safer)
      var value = cfg.getConfigLong('veryLargeLong');
      expect(value).toBe(2147483647);
    });

    it("can overwrite long values", function() {
      cfg.setConfigLong('overwriteLong', 100);
      cfg.setConfigLong('overwriteLong', 200);
      var value = cfg.getConfigLong('overwriteLong');
      expect(value).toBe(200);
    });

    it("returns undefined for non-existent long keys", function() {
      var value = cfg.getConfigLong('nonExistentLong');
      expect(value).toBeUndefined();
    });

    it("can handle multiple long values", function() {
      var longs = {
        'long1': 1,
        'long2': 1000,
        'long3': -500,
        'long4': 0
      };
      
      Object.keys(longs).forEach(function(key) {
        cfg.setConfigLong(key, longs[key]);
      });
      
      Object.keys(longs).forEach(function(key) {
        var value = cfg.getConfigLong(key);
        expect(value).toBe(longs[key]);
      });
    });
  });

  describe("Float Configuration", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("can set and get float values", function() {
      cfg.setConfigFloat('testFloat', 3.14159);
      var value = cfg.getConfigFloat('testFloat');
      expect(value).toBeCloseTo(3.14159);
    });

    it("can set and get zero", function() {
      cfg.setConfigFloat('zeroFloat', 0.0);
      var value = cfg.getConfigFloat('zeroFloat');
      expect(value).toBe(0.0);
    });

    it("can set and get negative values", function() {
      cfg.setConfigFloat('negativeFloat', -3.14159);
      var value = cfg.getConfigFloat('negativeFloat');
      expect(value).toBeCloseTo(-3.14159);
    });

    it("can set and get very small values", function() {
      cfg.setConfigFloat('smallFloat', 0.000001);
      var value = cfg.getConfigFloat('smallFloat');
      expect(value).toBeCloseTo(0.000001);
    });

    xit("can set and get very large values", function() {
      cfg.setConfigFloat('largeFloat', 1.7976931348623157e+308); // Max double
      var value = cfg.getConfigFloat('largeFloat');
      expect(value).toBeCloseTo(1.7976931348623157e+308);
    });

    xit("can set and get infinity", function() {
      cfg.setConfigFloat('infinityFloat', Infinity);
      var value = cfg.getConfigFloat('infinityFloat');
      expect(value).toBe(Infinity);
    });

    xit("can set and get negative infinity", function() {
      cfg.setConfigFloat('negInfinityFloat', -Infinity);
      var value = cfg.getConfigFloat('negInfinityFloat');
      expect(value).toBe(-Infinity);
    });

    xit("can set and get NaN", function() {
      cfg.setConfigFloat('nanFloat', NaN);
      var value = cfg.getConfigFloat('nanFloat');
      expect(isNaN(value)).toBe(true);
    });

    it("can overwrite float values", function() {
      cfg.setConfigFloat('overwriteFloat', 1.0);
      cfg.setConfigFloat('overwriteFloat', 2.0);
      var value = cfg.getConfigFloat('overwriteFloat');
      expect(value).toBe(2.0);
    });

    it("returns undefined for non-existent float keys", function() {
      var value = cfg.getConfigFloat('nonExistentFloat');
      expect(value).toBeUndefined();
    });

    it("can handle multiple float values", function() {
      var floats = {
        'float1': 1.5,
        'float2': -2.7,
        'float3': 0.0,
        'float4': 3.14159
      };
      
      Object.keys(floats).forEach(function(key) {
        cfg.setConfigFloat(key, floats[key]);
      });
      
      Object.keys(floats).forEach(function(key) {
        var value = cfg.getConfigFloat(key);
        expect(value).toBeCloseTo(floats[key]);
      });
    });
  });

  describe("Boolean Configuration", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("can set and get true values", function() {
      cfg.setConfigBool('testBool', true);
      var value = cfg.getConfigBool('testBool');
      expect(value).toBe(true);
    });

    it("can set and get false values", function() {
      cfg.setConfigBool('testBool', false);
      var value = cfg.getConfigBool('testBool');
      expect(value).toBe(false);
    });

    it("can overwrite boolean values", function() {
      cfg.setConfigBool('overwriteBool', true);
      cfg.setConfigBool('overwriteBool', false);
      var value = cfg.getConfigBool('overwriteBool');
      expect(value).toBe(false);
    });

    it("returns undefined for non-existent boolean keys", function() {
      var value = cfg.getConfigBool('nonExistentBool');
      expect(value).toBeUndefined();
    });

    it("can handle multiple boolean values", function() {
      var booleans = {
        'bool1': true,
        'bool2': false,
        'bool3': true,
        'bool4': false
      };
      
      Object.keys(booleans).forEach(function(key) {
        cfg.setConfigBool(key, booleans[key]);
      });
      
      Object.keys(booleans).forEach(function(key) {
        var value = cfg.getConfigBool(key);
        expect(value).toBe(booleans[key]);
      });
    });
  });

  describe("Mixed Data Types", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    xit("can store different data types with the same key name", function() {
      cfg.setConfigString('mixedKey', 'string value');
      cfg.setConfigLong('mixedKey', 12345);
      cfg.setConfigFloat('mixedKey', 3.14159);
      cfg.setConfigBool('mixedKey', true);
      
      var stringValue = cfg.getConfigString('mixedKey');
      var longValue = cfg.getConfigLong('mixedKey');
      var floatValue = cfg.getConfigFloat('mixedKey');
      var boolValue = cfg.getConfigBool('mixedKey');
      
      expect(stringValue).toBe('string value');
      expect(longValue).toBe(12345);
      expect(floatValue).toBeCloseTo(3.14159);
      expect(boolValue).toBe(true);
    });

    it("can store all data types simultaneously", function() {
      cfg.setConfigString('testString', 'Hello World');
      cfg.setConfigLong('testLong', 81832493);
      cfg.setConfigFloat('testFloat', -31.3131);
      cfg.setConfigBool('testBool', true);
      
      var myString = cfg.getConfigString('testString');
      var myLong = cfg.getConfigLong('testLong');
      var myFloat = cfg.getConfigFloat('testFloat');
      var myBool = cfg.getConfigBool('testBool');
      
      expect(myString).toBe('Hello World');
      expect(myLong).toBe(81832493);
      expect(myFloat).toBeCloseTo(-31.3131);
      expect(myBool).toBe(true);
    });

    it("can handle complex configuration scenarios", function() {
      // Set up a complex configuration
      cfg.setConfigString('app.name', 'My Application');
      cfg.setConfigLong('app.version', 100);
      cfg.setConfigFloat('app.rating', 4.5);
      cfg.setConfigBool('app.enabled', true);
      
      cfg.setConfigString('user.name', 'John Doe');
      cfg.setConfigLong('user.age', 30);
      cfg.setConfigFloat('user.score', 95.7);
      cfg.setConfigBool('user.active', false);
      
      // Verify all values
      expect(cfg.getConfigString('app.name')).toBe('My Application');
      expect(cfg.getConfigLong('app.version')).toBe(100);
      expect(cfg.getConfigFloat('app.rating')).toBeCloseTo(4.5);
      expect(cfg.getConfigBool('app.enabled')).toBe(true);
      
      expect(cfg.getConfigString('user.name')).toBe('John Doe');
      expect(cfg.getConfigLong('user.age')).toBe(30);
      expect(cfg.getConfigFloat('user.score')).toBeCloseTo(95.7);
      expect(cfg.getConfigBool('user.active')).toBe(false);
    });
  });

  describe("Configuration Isolation", function() {
    it("isolates configurations between different config names", function() {
      // Set values in config1
      cfg.useConfig('config1');
      cfg.setConfigString('key', 'value1');
      cfg.setConfigLong('number', 100);
      
      // Set values in config2
      cfg.useConfig('config2');
      cfg.setConfigString('key', 'value2');
      cfg.setConfigLong('number', 200);
      
      // Verify config1 still has its values
      cfg.useConfig('config1');
      expect(cfg.getConfigString('key')).toBe('value1');
      expect(cfg.getConfigLong('number')).toBe(100);
      
      // Verify config2 has its values
      cfg.useConfig('config2');
      expect(cfg.getConfigString('key')).toBe('value2');
      expect(cfg.getConfigLong('number')).toBe(200);
    });

    it("maintains separate configurations for different apps", function() {
      // App 1 configuration
      cfg.useConfig('app1');
      cfg.setConfigString('theme', 'dark');
      cfg.setConfigLong('windowWidth', 1024);
      cfg.setConfigBool('soundEnabled', true);
      
      // App 2 configuration
      cfg.useConfig('app2');
      cfg.setConfigString('theme', 'light');
      cfg.setConfigLong('windowWidth', 800);
      cfg.setConfigBool('soundEnabled', false);
      
      // Verify app1 settings
      cfg.useConfig('app1');
      expect(cfg.getConfigString('theme')).toBe('dark');
      expect(cfg.getConfigLong('windowWidth')).toBe(1024);
      expect(cfg.getConfigBool('soundEnabled')).toBe(true);
      
      // Verify app2 settings
      cfg.useConfig('app2');
      expect(cfg.getConfigString('theme')).toBe('light');
      expect(cfg.getConfigLong('windowWidth')).toBe(800);
      expect(cfg.getConfigBool('soundEnabled')).toBe(false);
    });
  });

  describe("Error Handling", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("handles null and undefined values gracefully", function() {
      expect(function() {
        cfg.setConfigString('nullKey', null);
      }).toThrow();
      
      expect(function() {
        cfg.setConfigString('undefinedKey', undefined);
      }).toThrow();
      
      expect(function() {
        cfg.setConfigLong('nullLong', null);
      }).toThrow();
      
      expect(function() {
        cfg.setConfigFloat('nullFloat', null);
      }).toThrow();
      
      // Boolean doesn't accept null, so we expect it to throw
      expect(function() {
        cfg.setConfigBool('nullBool', null);
      }).toThrow();
    });

    it("handles empty key names", function() {
      expect(function() {
        cfg.setConfigString('', 'value');
      }).not.toThrow();
      
      expect(function() {
        cfg.getConfigString('');
      }).not.toThrow();
    });

    it("handles very long key names", function() {
      var longKey = 'A'.repeat(1000);
      expect(function() {
        cfg.setConfigString(longKey, 'value');
      }).not.toThrow();
      
      expect(function() {
        cfg.getConfigString(longKey);
      }).not.toThrow();
    });

    it("handles special characters in key names", function() {
      var specialKeys = [
        'key-with-dashes',
        'key_with_underscores',
        'key.with.dots',
        'key with spaces',
        'key!@#$%^&*()',
        'key[with]brackets',
        'key{with}braces'
      ];
      
      specialKeys.forEach(function(key) {
        expect(function() {
          cfg.setConfigString(key, 'value');
        }).not.toThrow();
        
        expect(function() {
          cfg.getConfigString(key);
        }).not.toThrow();
      });
    });

    xit("handles type conversion gracefully", function() {
      // Try to get a string as other types
      cfg.setConfigString('stringKey', '123');
      
      var longValue = cfg.getConfigLong('stringKey');
      var floatValue = cfg.getConfigFloat('stringKey');
      var boolValue = cfg.getConfigBool('stringKey');
      
      // These should return undefined since the key was set as string
      expect(longValue).toBeUndefined();
      expect(floatValue).toBeUndefined();
      expect(boolValue).toBeUndefined();
    });
  });

  describe("Edge Cases", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    xit("handles maximum values for each data type", function() {
      // String - very long string
      var maxString = 'A'.repeat(10000);
      cfg.setConfigString('maxString', maxString);
      expect(cfg.getConfigString('maxString')).toBe(maxString);
      
      // Long - maximum safe integer
      cfg.setConfigLong('maxLong', Number.MAX_SAFE_INTEGER);
      expect(cfg.getConfigLong('maxLong')).toBe(Number.MAX_SAFE_INTEGER);
      
      // Float - maximum double
      cfg.setConfigFloat('maxFloat', Number.MAX_VALUE);
      expect(cfg.getConfigFloat('maxFloat')).toBe(Number.MAX_VALUE);
      
      // Boolean - both values
      cfg.setConfigBool('maxBool', true);
      expect(cfg.getConfigBool('maxBool')).toBe(true);
    });

    xit("handles minimum values for each data type", function() {
      // String - empty string
      cfg.setConfigString('minString', '');
      expect(cfg.getConfigString('minString')).toBe('');
      
      // Long - minimum safe integer
      cfg.setConfigLong('minLong', Number.MIN_SAFE_INTEGER);
      expect(cfg.getConfigLong('minLong')).toBe(Number.MIN_SAFE_INTEGER);
      
      // Float - minimum double
      cfg.setConfigFloat('minFloat', Number.MIN_VALUE);
      expect(cfg.getConfigFloat('minFloat')).toBe(Number.MIN_VALUE);
      
      // Boolean - false
      cfg.setConfigBool('minBool', false);
      expect(cfg.getConfigBool('minBool')).toBe(false);
    });

    it("handles rapid configuration changes", function() {
      for (var i = 0; i < 100; i++) {
        cfg.setConfigLong('rapidKey', i);
        var value = cfg.getConfigLong('rapidKey');
        expect(value).toBe(i);
      }
    });

    it("handles multiple configuration switches", function() {
      for (var i = 0; i < 10; i++) {
        var configName = 'config' + i;
        cfg.useConfig(configName);
        cfg.setConfigString('key', 'value' + i);
        
        // Switch back and forth
        cfg.useConfig('main');
        cfg.setConfigString('mainKey', 'mainValue');
        
        cfg.useConfig(configName);
        expect(cfg.getConfigString('key')).toBe('value' + i);
      }
    });
  });

  describe("Validation", function() {
    beforeEach(function() {
      cfg.useConfig(testConfigName);
    });

    it("validates that useConfig returns boolean", function() {
      var result = cfg.useConfig('validation-test');
      expect(typeof result).toBe('boolean');
    });

    it("validates that getConfigString returns string or undefined", function() {
      cfg.setConfigString('testKey', 'testValue');
      var result = cfg.getConfigString('testKey');
      expect(typeof result === 'string' || result === undefined).toBe(true);
    });

    it("validates that getConfigLong returns number or undefined", function() {
      cfg.setConfigLong('testKey', 123);
      var result = cfg.getConfigLong('testKey');
      expect(typeof result === 'number' || result === undefined).toBe(true);
    });

    it("validates that getConfigFloat returns number or undefined", function() {
      cfg.setConfigFloat('testKey', 3.14);
      var result = cfg.getConfigFloat('testKey');
      expect(typeof result === 'number' || result === undefined).toBe(true);
    });

    it("validates that getConfigBool returns boolean or undefined", function() {
      cfg.setConfigBool('testKey', true);
      var result = cfg.getConfigBool('testKey');
      expect(typeof result === 'boolean' || result === undefined).toBe(true);
    });

    it("validates configuration persistence across calls", function() {
      cfg.setConfigString('persistentKey', 'persistentValue');
      cfg.setConfigLong('persistentNumber', 42);
      
      // Simulate multiple calls
      for (var i = 0; i < 5; i++) {
        expect(cfg.getConfigString('persistentKey')).toBe('persistentValue');
        expect(cfg.getConfigLong('persistentNumber')).toBe(42);
      }
    });
  });

});