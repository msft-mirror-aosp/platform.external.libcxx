"""Test format for the NDK tests."""
import libcxx.android.test.format


def prune_xfails(test):
    """Removes most xfail handling from tests.

    We need to keep some xfail handling because some tests in libc++ that
    really should be using REQUIRES actually used XFAIL (i.e. `XFAIL: c++11`).
    """
    test.xfails = [x for x in test.xfails if x.startswith('c++')]


class TestFormat(libcxx.android.test.format.TestFormat):
    """Loose wrapper around the Android format that disables XFAIL handling."""

    def _evaluate_pass_test(self, test, tmp_base, lit_config):
        """Clears the test's xfail list before delegating to the parent."""
        prune_xfails(test)
        return super(TestFormat, self)._evaluate_pass_test(
            test, tmp_base, lit_config)

    def _evaluate_fail_test(self, test):
        """Clears the test's xfail list before delegating to the parent."""
        prune_xfails(test)
        return super(TestFormat, self)._evaluate_fail_test(test)
