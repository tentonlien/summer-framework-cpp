#include <org/summerframework/core.h>

void ApplicationContext::loadData() {
{{repeat-start id=0}}    this -> setApplicationProperty("{{data-key}}", "{{data-value}}");{{repeat-end}}
    this -> setApplicationName("{{applicationName}}");
}