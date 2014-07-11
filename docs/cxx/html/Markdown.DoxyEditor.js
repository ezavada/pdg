(function () {

	var activeDoxyEditor = false;
	var activeDoxyInput = false;
	var doxyConverter;
	var doxyClassName;
	var jsClassName;

	$(document).ready(function() {
		setupDoxyEditor();
	});

	function setupDoxyEditor() {
		doxyConverter = Markdown.getDoxygenConverter();
		var s = window.location.pathname;
		doxyClassName = s.substring(s.lastIndexOf('/')+1).replace('.html', '');
		jsClassName = $('#nav-path li:last-child').text();
		installDoxyEditButtons();
	}

	function funcPrototypeToMangledName(ps) {
		if (!ps.match(/\(/)) {
			// not actually a function prototype, probably a class constant
			ps = ps.toLowerCase().replace(/(\S+) = \S+/g,'@$1');  // mark as @constantname
			ps = ps.replace(/ /g, ''); //get rid of all remaining spaces
		} else {
			// used: bcd f i  mnopqrs uv x 0 8 @
			ps = ps.replace(/\).*/, ''); // get rid of trailing paren and anything after it
			ps = ps.match(/\S+\(.*/).toString().toLowerCase();
			ps = ps.replace(/(\S+) = \S+,?/g,'$1,');  // get rid of default params
			ps = ps.replace(/(\S+) \S+,?/g,'$1 '); // get rid of param names
			ps = ps.replace(/\(/, '- '); // get rid of leading paren
			ps = ps.replace(/ boolean /g, ' b ');
			ps = ps.replace(/ color /g, ' c ');
			ps = ps.replace(/ offset /g, ' d ');
			ps = ps.replace(/ function /g, ' f ');
			ps = ps.replace(/ int /g, ' i ');
			ps = ps.replace(/ number /g, ' n ');
			ps = ps.replace(/ object /g, ' o ');
			ps = ps.replace(/ point /g, ' p ');
			ps = ps.replace(/ quad /g, ' q ');
			ps = ps.replace(/ rect /g, ' r ');
			ps = ps.replace(/ string /g, ' s ');
			ps = ps.replace(/ uint /g, ' u ');
			ps = ps.replace(/ vector /g, ' v ');
			ps = ps.replace(/ binarystring /g, ' 1 ');
			ps = ps.replace(/ memblock /g, ' m ');
			ps = ps.replace(/ buffer /g, ' 8 ');
			ps = ps.replace(/ (\S\S+) /g, ' _$1_ '); // mark everything else as _classname_
			ps = ps.replace(/ /g, ''); //get rid of all remaining spaces
			ps = ps.replace(/-$/, '-x');  // replace trailing - with -X for no params
		}
		return ps;
	}
	
	function installDoxyEditButtons() {
		// setup the class documentation block
		$('.textblock').before('<div class="doxyedit-button" id="'+doxyClassName+'"></div>');
		// setup the member documentation blocks
		$('.memdoc').each( function(index) {
			var ps = $(this).parent().find('.memproto').text();
			ps = ps.replace(/\s\s+/g, ' ');
			ps = ps.replace(/\s*\)\s*/, ')');
			ps = ps.replace(/\s*\(\s*/, '(');
			ps = funcPrototypeToMangledName(ps);
			var memberName = doxyClassName + '-' + ps;
			memberName = memberName.replace(/-pdg::/g, '_'); // get rid of any extra namespace stuff
			var jsName = $(this).parent().find('td.memname').text();
			jsName = jsName.replace(/\s$/, '');  // trim trailing whitespace
			if (ps.indexOf('@') < 0) {
				// function or class
				var i = jsName.lastIndexOf(' ');
				if (i != -1) {
					jsName = jsName.slice(i+1);
				}
			} else {
				// constant
				var i = jsName.indexOf(' ');
				if (i != -1) {
					jsName = jsName.slice(0, i);
				}
			}
			var jsMemberName = 'pdg::' + jsClassName + '::' + jsName;
			jsMemberName = jsMemberName.replace(/::::pdg/g, ''); // get rid of any extra namespace stuff
			if (!memberName.match(/related$/)) {  // don't add button for related methods
				$(this).before('<div class="doxyedit-button" id="'+memberName+'" title="'+jsMemberName+'"></div>');
			}
		});

		// make sure all the edit buttons know what to do when clicked
		$('.doxyedit-button').click(openDoxyEditor);
	}

	function openDoxyEditor() {
		closeActiveDoxyEditor();
		$(this).off('click');
		// create space for the editor in the div just below it
		var txtblock = $(this).next();
		var originaltxt = txtblock.html();
		var editcontainer = '<div class="doxyedit-pane"><div class="wmd-panel">'+
		'<div id="wmd-button-bar"></div><textarea class="wmd-input" id="wmd-input">' +
		'</textarea></div><div id="wmd-preview" class="wmd-panel wmd-preview"></div></div>';
		txtblock.html(editcontainer);
		// create the editor
		activeDoxyEditor = new Markdown.Editor(doxyConverter);
		activeDoxyEditor.txtblock = txtblock;
		activeDoxyEditor.originaltxt = originaltxt;
		activeDoxyEditor.run();
		activeDoxyEditor.filename = $(this).attr('id');
		activeDoxyEditor.jsMemberName = $(this).attr('title');
		activeDoxyInput = activeDoxyEditor.txtblock.find('.wmd-input');
		loadDox(activeDoxyEditor.filename, activeDoxyInput);
		$(this).click(function() {
			$(this).off('click');
			$(this).click(openDoxyEditor);  // restore our click handler
			closeActiveDoxyEditor();
		});
	}

	function closeActiveDoxyEditor() {
		if (!activeDoxyEditor) {
			return;
		}
		var markdown = activeDoxyEditor.txtblock.find('.wmd-input').val();
		var preview = activeDoxyEditor.txtblock.find('.wmd-preview');
		var filename = activeDoxyEditor.filename;
		var jsName = activeDoxyEditor.jsMemberName;
		activeDoxyEditor.txtblock.html(preview.html());
		activeDoxyEditor = false;
		saveDox(filename, markdown, jsName);
	}

	function doxifyMarkdown(data, item, jsName) {
		// make sure we have comments around the lines
		if (!data.match(/^namespace pdg \{ \/\*\*\n\n/m)) {
			data = "namespace pdg { /**\n\n"+data;
		} 
		if (data.indexOf('\n\n**/ }') < 0) {
			data = data + '\n\n**/ }';
		}
		if (item.indexOf('-') < 0) {
			// find the class info or insert it if missing
			if (!data.match(/\\class /)) {
				data = data.replace(/^namespace pdg \{ \/\*\*/, 
					'namespace pdg { /**\n\n\\class pdg::'+jsClassName);
			}
		} else if (item.indexOf('@') >= 0) {
			// find the constant/enum/variable info or insert it if missing
			if (!data.match(/\\var/)) {
				data = data.replace(/^namespace pdg \{ \/\*\*/, 
					'namespace pdg { /**\n\n\\var '+jsName);
			}			
		} else {
			// find the function info or insert it if missing
			if (!data.match(/\\fn /)) {
				data = data.replace(/^namespace pdg \{ \/\*\*/, 
					'namespace pdg { /**\n\n\\fn '+jsName);
			}
		}
		data = data.replace(/\\\\/g, '\\'); // replace double backslashes with single backslash
		return data;
	}
	
	function htmlToDoxyMarkdown(html) {
		html = html.replace(/\n/g, '');
		html = html.replace(/<br\/>/g, '\n');
		html = html.replace(/<br>/g, '\n');
		html = html.replace(/<\/p>/g, '\n');
		html = html.replace(/<p>/g, '');
		html = html.replace(/<td class=\"paramname\">/g, '\n\\param ');
		html = html.replace(/<\/td><td>/g, ' ');
		html = html.replace(/<dt>Parameters<\/dt>/g, '');
		html = html.replace(/<[^>]*>/g, ''); // remove all remaining html tags
		html = '\\brief '+ html;  // first line is the brief description
		return html;
	}

	function saveDox(doxname, markdown, jsName) {
		data = doxifyMarkdown(markdown, doxname, jsName);
		$.post('savedoc.php', 
			{ 
				docName: doxname, 
				docContents: data 
			}, 
			function(data, status, xhr) {
//				alert('data: '+ data + ' status: ' + status, ' xhr: ' + xhr);
				// do something about an error!
			}
		);
	}

	function loadDox(doxname, inputEl) {
		$.get('getdoc.php?name='+doxname,function(data, status, xhr) {
			data = doxifyMarkdown(data, doxname, activeDoxyEditor.jsMemberName);
			inputEl.val(data);
			activeDoxyEditor.refreshPreview();
		}).error(function() {
			data = htmlToDoxyMarkdown(activeDoxyEditor.originaltxt);
			inputEl.val(data);
			activeDoxyEditor.refreshPreview();
		});
	}
	
})();
