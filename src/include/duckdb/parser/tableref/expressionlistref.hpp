//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/tableref/expressionlistref.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/tableref.hpp"
#include "duckdb/parser/parsed_expression.hpp"

namespace duckdb {
//! Represents an expression list as generated by a VALUES statement
class ExpressionListRef : public TableRef {
public:
	ExpressionListRef() : TableRef(TableReferenceType::EXPRESSION_LIST) {
	}

	//! Value list, only used for VALUES statement
	vector<vector<unique_ptr<ParsedExpression>>> values;
	//! Expected SQL types
	vector<SQLType> expected_types;
	//! The set of expected names
	vector<string> expected_names;

public:
	bool Equals(const TableRef *other_) const override;

	unique_ptr<TableRef> Copy() override;

	//! Serializes a blob into a ExpressionListRef
	void Serialize(Serializer &serializer) override;
	//! Deserializes a blob back into a ExpressionListRef
	static unique_ptr<TableRef> Deserialize(Deserializer &source);
};
} // namespace duckdb