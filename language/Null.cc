
#include "Null.h"

std::optional<std::pair<Null*, std::string>> Null::parse(
	const std::string& text) {

  auto str = extract_whitespace(text).second;

  if (auto null = tag(str, "null"))
	return std::make_pair(new Null, null->second);

  return std::nullopt;
}
