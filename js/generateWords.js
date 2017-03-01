const fs = require("fs");
const _ = require("lodash");
const async = require("async");

let consonantStr = fs.readFileSync("../consonants.txt", {encoding: "utf8"});
let vowelStr = fs.readFileSync("../vowels.txt", {encoding: "utf8"});

let consonants = consonantStr.split("\n");
let vowels = vowelStr.split("\n");

permutation(consonants, vowels, function(words){
	words = words.concat(vowels);
	fs.writeFile("../pinyin.txt", words.join("\n"), function(err){
		if(err) throw err;
	});
});

function permutation(arr1, arr2, cb){
	let results = [];
	let words = [];
	async.each(arr1, function(el1, callback){
		_.each(arr2, function(el2, i){
			words.push(el1 + el2);
		});
		callback();
	}, function(err){
		if(err){

		}else{
			cb(words);
		}
	});
}
