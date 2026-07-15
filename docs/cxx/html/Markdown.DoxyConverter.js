(function () {
    var output, Converter;
    if (typeof exports === "object" && typeof require === "function") { // we're in a CommonJS (e.g. Node.js) module
        output = exports;
        require("./Markdown.Sanitizer");
    } else {
        output = window.Markdown;
    }
     
    output.getDoxygenConverter = function () {
        var converter = Markdown.getSanitizingConverter();
        converter.hooks.chain("preConversion", stripDoxygenCommands);
        converter.hooks.chain("postConversion", convertDoxygenMarkup);
        return converter;
    }

	function stripDoxygenCommands (text) {
		// hide \fn lines
		text = text.replace(/[\\@]fn .*/ig, "");
		// hide \class lines
		text = text.replace(/[\\@]class .*/ig, "");
		// hide \var lines
		text = text.replace(/[\\@]var .*/ig, "");
		// hide \enum lines
		text = text.replace(/[\\@]enum .*/ig, "");
		// hide \struct lines
		text = text.replace(/[\\@]struct .*/ig, "");
		// hide \union lines
		text = text.replace(/[\\@]union .*/ig, "");
		// hide \def lines
		text = text.replace(/[\\@]def .*/ig, "");
		// hide \typedef lines
		text = text.replace(/[\\@]typedef .*/ig, "");
		// hide \file lines
		text = text.replace(/[\\@]file .*/ig, "");
		// hide \namespace lines
		text = text.replace(/[\\@]namespace .*/ig, "");
		// hide \package lines
		text = text.replace(/[\\@]package .*/ig, "");
		// hide \interface lines
		text = text.replace(/[\\@]interface .*/ig, "");
		// hide \mainpage lines
		text = text.replace(/[\\@]mainpage .*/ig, "");
		// hide \ingroup lines
		text = text.replace(/[\\@]ingroup .*/ig, "");
		// hide /* lines
		text = text.replace(/namespace pdg \{ \/\*\*/g, "");
		// hide */ lines
		text = text.replace(/\*\*\/ \}/g, "");
		// hide \todo lines, since we aren't showing them in the docs
		text = text.replace(/[\\@]todo .*/ig, "");
		// hide \related lines, since we aren't showing them in the docs
		text = text.replace(/[\\@]related .*/ig, "");
		text = text.replace(/[\\@]relatedalso .*/ig, "");
		text = text.replace(/[\\@]relates .*/ig, "");
		text = text.replace(/[\\@]relatesalso .*/ig, "");
		// hide \brief command
		text = text.replace(/[\\@]brief/ig, "");
		// hide \details command
		text = text.replace(/[\\@]details/ig, "");
		
		return text;
	}

	function convertDoxygenMarkup (html) {
		// format code blocks like doxygen does
		html = html.replace(/<pre>/g, "<pre class=\"fragment\">");
		// handle @note sections
		html = html.replace(/[\\@]note\s+(.*)/g, "<dl class=\"section note\"><dt>Note</dt><dd>$1</dd></dl>");
		// handle @warning sections
		html = html.replace(/[\\@]warning\s+(.*)/g, "<dl class=\"section warning\"><dt>Warning</dt><dd>$1</dd></dl>");
		// handle @bug sections
		html = html.replace(/[\\@]bug\s+(.*)/g, "<dl class=\"section bug\"><dt>Bug</dt><dd>$1</dd></dl>");
		// handle @author section
		html = html.replace(/[\\@]author\s+(.*)/g, "<dl class=\"section author\"><dt>Author</dt><dd>$1</dd></dl>");
		// handle @copyright section
		html = html.replace(/[\\@]copyright\s+(.*)/g, "<dl class=\"section copyright\"><dt>Copyright</dt><dd>$1</dd></dl>");
		// handle @version section
		html = html.replace(/[\\@]version\s+(.*)/g, "<dl class=\"section version\"><dt>Version</dt><dd>$1</dd></dl>");
		// handle @deprecated section
		html = html.replace(/[\\@]deprecated\s+(.*)/g, "<dl class=\"deprecated\"><dt><b><a class=\"el\">Deprecated</a></b></dt><dd>$1</dd></dl>");
		// handle @result & @return sections
		html = html.replace(/[\\@]return\s+(.*)/g, "<dl class=\"section return\"><dt>Returns</dt><dd>$1</dd></dl>");
		html = html.replace(/[\\@]result\s+(.*)/g, "<dl class=\"section return\"><dt>Returns</dt><dd>$1</dd></dl>");
		html = html.replace(/[\\@]returns\s+(.*)/g, "<dl class=\"section return\"><dt>Returns</dt><dd>$1</dd></dl>");
		// handle @pre & @post sections
		html = html.replace(/[\\@]pre\s+(.*)/g, "<dl class=\"section pre\"><dt>Precondition</dt><dd>$1</dd></dl>");
		html = html.replace(/[\\@]post\s+(.*)/g, "<dl class=\"section post\"><dt>Postcondition</dt><dd>$1</dd></dl>");
		// handle @remark section
		html = html.replace(/[\\@]remark\s+(.*)/g, "<dl class=\"section remark\"><dt>Remarks</dt><dd>$1</dd></dl>");
		// handle @since section
		html = html.replace(/[\\@]since\s+(.*)/g, "<dl class=\"section since\"><dt>Since</dt><dd>$1</dd></dl>");
		// setup param block at first \param command, and prep it for conversion
		paramPattern = /[\\@]param/i;
		html = html.replace(paramPattern, "<dl class=\"params\"><dt>Parameters</dt><dd>" +
			"<table class=\"params\"><tbody> @@_PARAM");
		var done = false;
		// convert all the \param tags to doxygen's HTML, and close
		// off the param block after the last one.
		do {
			if (paramPattern.test(html)) {
				// there is another param, convert the last one
				html = html.replace(/@@_PARAM\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr>");
				// now find and prep the new one
				html = html.replace(paramPattern, "@@_PARAM");
			} else {
				// there are no more, the last one we found was the end
				done = true;
				html = html.replace(/@@_PARAM\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr></tbody></table></dd></dl>");                    		
			}
		} while(!done);
		// handle #entityName sections (explicit references)
		html = html.replace(/\#(\S+)/g, "<a class=\"el\">$1</a>");
		// setup see also block at first \see or \sa command, and prep it for conversion
		saPattern = /[\\@]see |[\\@]sa /i;
		html = html.replace(saPattern, "<dl class=\"section see\"><dt>See Also</dt><dd>@@_SA ");
		done = false;
		// convert all the \sa tags to doxygen's HTML, and close
		// off the see also block after the last one.
		do {
			if (saPattern.test(html)) {
				// there is another see also, convert the last one
				html = html.replace(/@@_SA (.*)/, "<dd><a class=\"el\">$1</a></dd>");
				// now find and prep the new one
				html = html.replace(saPattern, "@@_SA ");
			} else {
				// there are no more, the last one we found was the end
				done = true;
				html = html.replace(/@@_SA (.*)/, "<dd><a class=\"el\">$1</a></dd></dl>");                    		
			}
		} while(!done);
		// setup exception/throw block at first \exception or \throws command, and prep it for conversion
		exceptionPattern = /[\\@]exception |[\\@]throws |[\\@]throw /i;
		html = html.replace(exceptionPattern, "<dl class=\"exception\"><dt>Exceptions</dt><dd>" +
			"<table class=\"exception\"><tbody> @@_EXCEPTION ");
		done = false;
		// convert all the \exception tags to doxygen's HTML, and close
		// off the exceptions block after the last one.
		do {
			if (exceptionPattern.test(html)) {
				// there is another see also, convert the last one
				html = html.replace(/@@_EXCEPTION\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr>");
				// now find and prep the new one
				html = html.replace(exceptionPattern, "@@_EXCEPTION ");
			} else {
				// there are no more, the last one we found was the end
				done = true;
				html =  html.replace(/@@_EXCEPTION\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr></tbody></table></dd></dl>");                   		
			}
		} while(!done);
		// setup retval block at first \retval command, and prep it for conversion
		retvalPattern = /[\\@]retval /i;
		html = html.replace(retvalPattern, "<dl class=\"retval\"><dt>Return values</dt><dd>" +
			"<table class=\"retval\"><tbody> @@_RETVAL ");
		done = false;
		// convert all the \retval tags to doxygen's HTML, and close
		// off the exceptions block after the last one.
		do {
			if (retvalPattern.test(html)) {
				// there is another see also, convert the last one
				html = html.replace(/@@_RETVAL\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr>");
				// now find and prep the new one
				html = html.replace(retvalPattern, "@@_RETVAL ");
			} else {
				// there are no more, the last one we found was the end
				done = true;
				html =  html.replace(/@@_RETVAL\s+(\S+)\s*(.*)/, "<tr><td class=\"paramname\">$1</td>" +
					"<td>$2</td></tr></tbody></table></dd></dl>");                   		
			}
		} while(!done);
		return html;
	}

})();
