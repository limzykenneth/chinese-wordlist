const fs = require("fs");
const _ = require("lodash");
const async = require("async");
const program = require("commander");
const pjson = require("./package.json");

function parseMinMax(val){
	if(val < 2){
		console.log("Minimum/Maximum value must be 2 or greater");
		process.exit();
	}else{
		return parseInt(val);
	}
}

program
	.version(pjson.version)
	.option("-o, --outfile [name]", "Specify output file of the generated wordlist")
	.option("-i, --infile [name]", "Specify input file", "./pinyin-curated.txt")
	.option("--min <n>", "Lower bound for number of words per line", parseMinMax, 2)
	.option("--max <n>", "Lower bound for number of words per line", parseMinMax, 2)
	.parse(process.argv);

if(!program.outfile){
	console.log("Please supply outfile name.");
	process.exit();
}
if(program.min > program.max){
	console.log(`Maximum value (${program.max}) must be greater than minimum value (${program.min}).`);
	process.exit();
}

let pinyinStr = fs.readFileSync(program.infile, {encoding: "utf8"});
let pinyinList = pinyinStr.split("\n");

fs.writeFileSync(program.outfile, "", {encoding: "utf8"});

let stream = fs.createWriteStream(program.outfile);

function recursionPermutation(arr, min, max, buffer, recur){
	let recurCount = recur;
	recurCount++;
	let minCount = min;
	let internalBuffer = buffer;

	async.each(arr, function(el, callback){
		internalBuffer += el;

		if(recurCount >= program.min){
			// write the word to file
			stream.write(internalBuffer + "\n");
			// console.log(internalBuffer + "\n");
		}
		// console.log(min, max);
		if(min <= max || recurCount < program.min){
			recursionPermutation(arr, minCount + 1, max, internalBuffer, recurCount);
		}

		minCount = min;
		internalBuffer = buffer;
		callback();
	});
}

recursionPermutation(pinyinList, program.min, program.max, "", 0);